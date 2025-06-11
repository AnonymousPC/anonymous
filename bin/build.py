import os
import re
import shutil
import subprocess
import sys



# Config

config = "debug"




# Platform

if sys.platform == "win32":
    system            = "windows"
    compiler          = "cl"
    executable_suffix = ".exe"
elif sys.platform == "linux":
    system            = "linux"
    compiler          = "g++"
    executable_suffix = ""
elif sys.platform == "darwin":
    system            = "macos"
    compiler          = "clang++"
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
        "-Wno-reserved-module-identifier",
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





# Command

class Error(Exception):
    pass

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
            raise Error(f"fatal error: {e.filename} not found")
        except subprocess.CalledProcessError as e:
            raise Error(e.stderr)

def compile(source_path, module_path, object_path):
    if compiler == "g++":
        commands = [f"g++ "
                    f"{' '.join(compile_args)} "
                    f"-I./lib/include "
                    f"{' '.join(f'-D{key}="{value}"' for key, value in define_args.items())} "
                    f"-c {source_path} "
                    f"-o {module_path}"]
    elif compiler == "clang++":
        commands = [f"clang++ "
                    f"{' '.join(compile_args)} "
                    f"-I./lib/include "
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
                    f"/I./lib/include "
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
        
def link(object_dir, executable_path):
    if compiler == "g++" or compiler == "clang++":
        commands = [f"{compiler} "
                    f"{' '.join(link_args)} "
                    f"{object_dir}/*.o "
                    f"-o {executable_path}"]
    elif compiler == "cl":
        commands = ["echo what??"]

    for command in commands:
        try:
            output = subprocess.run(command, shell=True, capture_output=True, check=True, text=True)
            print(output.stdout, end="", file=sys.stdout)
            print(output.stderr, end="", file=sys.stderr)       
        except subprocess.CalledProcessError as e:
            raise Error(e.stderr)
        
def cmake(module, dir):
    try:
        os.mkdir(f"./bin/cmake/{module}-build")
        os.mkdir(f"./bin/cmake/{module}-install")
    except:
        pass
    
    try:
        subprocess.run(f"cmake -S {dir} -B ./bin/cmake/{module}-build",                                     shell=True, capture_output=True, check=True, text=True)
        subprocess.run(f"cmake --build   ./bin/cmake/{module}-build",                                       shell=True, capture_output=True, check=True, text=True)
        subprocess.run(f"cmake --install ./bin/cmake/{module}-build --prefix=./bin/cmake/{module}-install", shell=True, capture_output=True, check=True, text=True)
    except subprocess.CalledProcessError as e:
        raise Error(e.stderr)
        
def autogen(dir):
    try:
        subprocess.run("./autogen.sh", shell=True, cwd=dir, capture_output=True, check=True, text=True)
    except subprocess.CalledProcessError as e:
        raise Error(e.stderr)
    
def configure(dir):
    try:
        subprocess.run("./configure", shell=True, cwd=dir, capture_output=True, check=True, text=True)
    except subprocess.CalledProcessError as e:
        raise Error(e.stderr)
    
def make(dir):
    try:
        subprocess.run("make", shell=True, cwd=dir, capture_output=True, check=True, text=True)
    except subprocess.CalledProcessError as e:
        raise Error(e.stderr)
    
def cp(module, file):
    file = file.strip("<>")
    try:
        shutil.copyfile(f"./bin/cmake/{module}-install/include/{file}", f"./lib/include/{file}")
    except Exception as e:
        raise Error(f"{e}")
    

    








# Module

class Module:
    modules = []
    current = 1
    total = 0

    def __init__(self, export, from_modules=[]):        
        try:
            self.export         = export
            self.source_path    = f"./include/{export.replace('.', '/')}.cpp"
            self.module_path    = f"./bin/module/{export}{module_suffix}"
            self.object_path    = f"./bin/module/{export}{object_suffix}"
            self.from_modules   = from_modules

            self.content        = preprocess(self.source_path)
            self.import_modules = [self._get_module(import_str) for import_str in re.findall(r'\bimport\s+([\w\.:]+)(?:\s*\[\[.*?\]\])*\s*;', self.content, flags=re.DOTALL)]
            self.is_built       = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_path) and os.path.getmtime(self.source_path) <= os.path.getmtime(self.module_path)

            if not self.is_built:
                Module.total += 1

            self._check_export()

        except Error as e:
            raise Error(f"In module imported from {self.export}:\n{e}")

    def build(self):
        try:
            for import_module in self.import_modules:
                if not import_module.is_built:
                    import_module.build()
            if not self.is_built:
                print(f"build module [{Module.current}/{Module.total}]: {self.export}")
                self._run_attribute()
                compile(source_path=self.source_path, module_path=self.module_path, object_path=self.object_path)
                self.is_built = True
                Module.current += 1
        except Error as e:
            raise Error(f"In module imported from {self.export}:\n{e}")

    def _get_module(self, import_str):
        for module in Module.modules:
            if module.export == import_str:
                return module
            
        if not import_str in self.from_modules:
            module = Module(import_str, self.from_modules + [self.export])
            Module.modules.append(module)
            return module
        else:
            raise Error(f"fatal error: dependency circle detected when trying to import module {import_str}")
        
    def _check_export(self):
        export_strs = re.findall(r'\bexport\s+module\s+([\w\.:]+)(?:\s*\[\[.*?\]\])*\s*;', self.content, flags=re.DOTALL)
        if len(export_strs) != 1 or export_strs[0] != self.export:
            raise Error(f"fatal error: file {self.source_path} should export module {self.export}")

    def _run_attribute(self):
        re_attr_key        = r'(?:[\w:]+)'                                             # cmake || gnu::always_inline
        re_attr_value      = r'(?:".*?")'                                              # "./CMakeLists.txt"
        re_attr_value_list = rf'(?:{re_attr_value}?(?:\s*,\s*{re_attr_value})*)'       # "./dir1/CMakeLists.txt", "./dir2/CMakeLists.txt"
        re_attr            = rf'({re_attr_key}(?:\s*\(\s*{re_attr_value_list}\s*\))?)' # cmake || cmake("./CMakeLists.txt")
        re_attr_list       = rf'(?:{re_attr}?(?:\s*,\s*{re_attr})*)'                   # cmake, autogen, configure
        re_attr_quote      = rf'(?:\[\[\s*{re_attr_list}\s*\]\])'                      # [[cmake, autogen, configure]]
        re_attr_quote_list = rf'(?:{re_attr_quote}?(?:\s*{re_attr_quote})*)'           # [[cmake, autogen, configuree]] [[makefile]] [[other]]

        for attributes in re.findall(re_attr_quote, self.content, flags=re.DOTALL): # Not to make match results overwritten in (attr_quote_list)*
            for attribute in attributes:
                if attribute != "":
                    args = re.findall(r'"(.*?)"', attribute)
                    if attribute.startswith("cmake"):
                        if len(args) != 1:
                            raise Error('error: module attribute [[cmake]] accepts 1 argument')
                        cmake(module=self.export, dir=args[0])
                    elif attribute.startswith("autogen"):
                        if len(args) != 1:
                            raise Error('error: module attribute [[autogen]] accepts 1 argument')
                        autogen(dir=args[0])
                    elif attribute.startswith("configure"):
                        if len(args) != 1:
                            raise Error('error: module attribute [[configure]] accepts 1 argument')
                        configure(dir=args[0])
                    elif attribute.startswith("make"):
                        if len(args) != 1:
                            raise Error('error: module attribute [[make]] accepts 1 argument')
                        make(dir=args[0])
                    elif attribute.startswith("cp"):
                        if len(args) != 1:
                            raise Error('error: module attribute [[cp]] accepts 1 argument')
                        cp(module=self.export, file=args[0])

        
        
        
            





# Main

if __name__ == "__main__":
    try:
        # Config
        if len(sys.argv) == 2 and sys.argv[1] in ["debug", "release", "clean"]:
            config = sys.argv[1]
        else:
            raise Error("fatal error: python build.py (debug|release|clean)")

        # Clear error outputs
        open("./bin/log.txt", 'w').write("")

        # Build
        if config == "debug" or config == "release":
            Module("main").build()
            link(object_dir="./bin/module", executable_path=f"./bin/main{executable_suffix}")
        
        # Clean
        elif config == "clean":
            for file in os.listdir("./bin/module"):
                if file != ".gitignore":
                    os.remove(f"./bin/module/{file}")
            for dir in os.listdir("./bin/cmake"):
                if dir != ".gitignore":
                    shutil.rmtree(f"./bin/module/{dir}")
    
    except Error as e:
        print(e, file=sys.stderr)
        print(e, file=open("./bin/log.txt", 'w'))
        exit(-1)

    except KeyboardInterrupt as e:
        exit(-1)
