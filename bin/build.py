import os
import re
import subprocess
import sys



# Config

config = "debug"




# Platform

if sys.platform == "win32":
    system = "windows"
elif sys.platform == "linux":
    system = "linux"
elif sys.platform == "darwin":
    system = "macos"

if system == "windows":
    compiler          = "cl"
    include_path      = ""
    lib_path          = ""
    libs              = ["advapi32", "bcrypt", "crypto", "kernel32", "mswsock", "ntdll", "shell32", "ssl", "stdc++exp", "tiff", "user32", "ws2_32"]
    executable_suffix = ".exe"
elif system == "linux":
    compiler          = "g++"
    include_path      = "/usr/include"
    lib_path          = "/usr/lib"
    libs              = []
    executable_suffix = ""
elif system == "macos":
    compiler          = "clang++"
    include_path      = "/opt/homebrew/include"
    lib_path          = "/opt/homebrew/lib"
    libs              = ["bz2", "hwloc", "iconv", "icudata", "icui18n", "icuio", "icutu", "icuuc", "jpeg", "lzma", "png", "tiff", "tiffxx", "z", "zstd"]
    executable_suffix = ""

if compiler == "g++":
    compile_args = [
        "-std=c++26", 
        "-g",
        "-Wall", 
        "-fdiagnostics-color=always",
        "-fmodules"
        "-Wno-reserved-module-identifier"
    ]
    if config == "debug":
        compile_args.append("-O0")
        compile_args.append("-fno-inline")
    elif config == "release":
        compile_args.append("-O3")
        compile_args.append("-DNDEBUG")
    link_args = ["-fdiagnostics-color=always"]
    module_suffix = ".gcm"
    object_suffix = ".o"
elif compiler == "clang++":
    compile_args = [
        "-std=c++26", 
        "-g", 
        "-Wall", 
        "-fdiagnostics-color=always",
        "-fprebuilt-module-path=./bin/module",
        "-Wno-reserved-module-identifier"
    ]
    if config == "debug":
        compile_args.append("-O0")
        compile_args.append("-fno-inline")
    elif config == "release":
        compile_args.append("-O3")
        compile_args.append("-DNDEBUG")
    link_args = ["-fdiagnostics-color=always"]
    module_suffix = ".pcm"
    object_suffix = ".o"
elif compiler == "cl":
    compile_args = [
        "/std:c++latest",
        "/EHsc",
        "/Z7",
        "/W4"
    ]
    if config == "debug":
        compile_args.append("/Od")
    elif config == "release":
        compile_args.append("/O2")
        compile_args.append("/DNDEBUG")

    link_args = []
    module_suffix = ".ifc"
    object_suffix = ".obj"

define_args = {
    "abstract": '0', 
    "extends" : ':',
    "in"      : ':', 
    "self"    : "(*this)"
}


class Error(Exception):
    def __init__(self, message, prefix=""):
        if type(message) == str:
            self.message = message
            self.prefix = prefix
        elif type(message) == Error:
            self.message = message.message
            self.prefix = f"{prefix}\n{message.prefix}"
        else:
            assert False

    def __str__(self):
        return f"{self.prefix}\n{self.message}"

def preprocess(source_path):
    if compiler == "g++" or compiler == "clang++":    
        commands = [f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f"-E -x c++ - "
                    f"-o -"]
    elif compiler == "cl":
        commands = [f"{compiler} "
                    f"/E {source_path}"]

    for command in commands: 
        try:
            reader = open(source_path, 'r').read()
            reader = re.sub(r'^\s*#\s*include.*$', "", reader, flags=re.MULTILINE)
            return subprocess.run(command, shell=True, capture_output=True, check=True, text=True, input=reader).stdout
        except FileNotFoundError as e:
            raise Error(e.filename)
        except subprocess.CalledProcessError as e:
            raise Error(e.stderr)

def compile(source_path, module_path, object_path):
    if compiler == "g++":
        commands = [f"g++ "
                    f"{' '.join(compile_args)} "
                    f"-I{include_path} "
                    f"{' '.join(f'-D{key}="{value}"' for key, value in define_args.items())} "
                    f"-c {source_path} "
                    f"-o {module_path}"]
    elif compiler == "clang++":
        commands = [f"clang++ "
                    f"{' '.join(compile_args)} "
                    f"-I{include_path} "
                    f"{' '.join(f'-D{key}="{value}"' for key, value in define_args.items())} "
                    f"--precompile -x c++-module {source_path} "
                    f"-o                         {module_path}",
                    
                    f"clang++ "
                    f"{' '.join(compile_args)} "
                    f"-c {module_path} "
                    f"-o {object_path}"]
    elif compiler == "cl":
        commands = [f"cl "
                    f"{' '.join(compile_args)} "
                    f"/I{include_path} "
                    f"{' '.join(f'/D{key}="{value}"' for key, value in define_args.items())} "
                    f"/c /interface /TP {source_path} "
                    f"/ifcOutput        {module_path} "
                    f"/Fo               {object_path}"]
        
    for command in commands:
        try:
            output = subprocess.run(command, shell=True, capture_output=True, check=True, text=True)
            print(output.stdout, end="", file=sys.stdout)
            print(output.stderr, end="", file=sys.stderr)       
        except subprocess.CalledProcessError as e:
            raise Error(e.stderr)

def link(object_dir, exe_path):
    if compiler == "g++" or compiler == "clang++":
        commands = [f"{compiler} "
                    f"{' '.join(link_args)} "
                    f"{object_dir}/*.o "
                    f"-L{lib_path} "
                    f"{' '.join(f"-l{lib}" for lib in libs)} "
                    f"-o {exe_path}"]
    elif compiler == "cl":
        commands = ["echo what??"]

    for command in commands:
        try:
            output = subprocess.run(command, shell=True, capture_output=True, check=True, text=True)
            print(output.stdout, end="", file=sys.stdout)
            print(output.stderr, end="", file=sys.stderr)       
        except subprocess.CalledProcessError as e:
            raise Error(e.stderr)
        


# Module

class Module:
    modules = []
    current = 1
    total = 0

    def __init__(self, export, required_by=[]):
        self.export      = export
        self.source_path = f"./include/{export.replace('.', '/')}.cpp"
        self.module_path = f"./bin/module/{export}{module_suffix}"
        self.object_path = f"./bin/module/{export}{object_suffix}"
        self.required_by = required_by
        
        content = preprocess(self.source_path)
        try:
            self.import_modules = [self.get_module(import_str) for import_str in re.findall(r'^\s*(?:export)?\s*import\s+([\w\.:]+)\s*;\s*$', content, re.MULTILINE)]
        except Error as e:
            raise Error(e, prefix=f"In module imported from {self.export}:")
        self.is_built = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_path) and os.path.getmtime(self.source_path) <= os.path.getmtime(self.module_path)
        if not self.is_built:
            Module.total += 1

        export_strs = re.findall(r'^\s*export\s+module\s+([\w\.:]+)\s*;\s*$', content, re.MULTILINE)
        if len(export_strs) != 1 or export_strs[0] != self.export:
            raise Error(f"fatal error: file {self.source_path} should export module {self.export}")

    def build(self):
        for import_module in self.import_modules:
            if not import_module.is_built:
                try:
                    import_module.build()
                except Error as e:
                    raise Error(e, prefix=f"In module imported from {self.export}:")
            
        if not self.is_built:
            print(f"build module [{Module.current}/{Module.total}]: {self.export}")
            compile(source_path=self.source_path, module_path=self.module_path, object_path=self.object_path)
            self.is_built = True
            Module.current += 1

    def get_module(self, import_str):
        for module in Module.modules:
            if module.export == import_str:
                return module
            
        if not import_str in self.required_by:
            module = Module(import_str, self.required_by + [self.export])
            Module.modules.append(module)
            return module
        else:
            raise Error(f"fatal error: dependency circle detected when importing {import_str}")
    
class Object:
    def __init__(self, export):
        pass

    def build(self):
        link(object_dir="./bin/module", exe_path=f"./bin/main{executable_suffix}")
    



# Main

if __name__ == "__main__":
    try:
        # Config
        if len(sys.argv) == 2 and sys.argv[1] in ["debug", "release", "clean"]:
            config = sys.argv[1]
        else:
            raise Error("fatal error: python build.py debug|release|clean")

        # Clear error outputs
        open("./bin/log.txt", 'w').write("")

        # Build
        if config == "debug" or config == "release":
            Module("main").build()
            Object("main").build()
        
        # Clean
        elif config == "clean":
            for file in os.listdir("./bin/module"):
                os.remove(f"./bin/module/{file}")
    
    except Error as e:
        print(e, file=sys.stderr)
        print(e, file=open("./bin/log.txt", 'w'))
        exit(-1)

    except KeyboardInterrupt as e:
        exit(-1)
