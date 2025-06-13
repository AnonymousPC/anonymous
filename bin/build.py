import argparse
import os
import re
import shutil
import subprocess
import sys
import threading

# Environment
os.chdir(f"{os.path.dirname(__file__)}/..")






# Config

type = "debug"




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
        "-fmodules",
        "-Wno-reserved-module-identifier",
        "-Wno-unknown-attributes"
    ]
    if type == "debug":
        compile_args.append("-O0")
        compile_args.append("-fno-inline")
    elif type == "release":
        compile_args.append("-O3")
        compile_args.append("-DNDEBUG")
    link_args = ["-fdiagnostics-color=always"]
    module_suffix  = ".gcm"
    object_suffix  = ".o"
    library_suffix = ".a"
elif compiler == "clang++":
    compile_args = [
        "-std=c++26", 
        "-g", 
        "-Wall", 
        "-fdiagnostics-color=always",
       f"-fprebuilt-module-path=./bin/{type}/module",
        "-Wno-reserved-module-identifier",
        "-Wno-unknown-attributes"
    ]
    if type == "debug":
        compile_args.append("-O0")
        compile_args.append("-fno-inline")
    elif type == "release":
        compile_args.append("-O3")
        compile_args.append("-DNDEBUG")
    link_args = ["-fdiagnostics-color=always"]
    module_suffix  = ".pcm"
    object_suffix  = ".o"
    library_suffix = ".a"
elif compiler == "cl":
    compile_args = [
        "/std:c++latest",
        "/EHsc",
        "/Z7",
        "/W4"
    ]
    if type == "debug":
        compile_args.append("/Od")
    elif type == "release":
        compile_args.append("/O2")
        compile_args.append("/DNDEBUG")
    link_args = []
    module_suffix  = ".ifc"
    object_suffix  = ".obj"
    library_suffix = ".lib"

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
        
def link(executable_path):
    if compiler == "g++" or compiler == "clang++":
        commands = [f"{compiler} "
                    f"{' '.join(link_args)} "
                    f"./bin/{type}/module/*{object_suffix} "
                    f"./bin/{type}/module/*{library_suffix} "
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
        

    







# Module

class Module:
    modules = []
    current = 1
    total = 0

    def __init__(self, export, from_modules=[]):        
        try:
            self.export         = export
            self.source_path    = f"./include/{export.replace('.', '/')}.cpp"
            self.module_path    = f"./bin/{type}/module/{export}{module_suffix}"
            self.object_path    = f"./bin/{type}/module/{export}{object_suffix}"
            self.from_modules   = from_modules

            self.content        = preprocess(self.source_path)
            self.import_modules = [self._get_module(import_str) for import_str in re.findall(r'\bimport\s+([\w\.:]+)(?:\s*\[\[.*?\]\])*\s*;', self.content, flags=re.DOTALL)]
            self.is_built       = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_path) and os.path.getmtime(self.source_path) <= os.path.getmtime(self.module_path)

            if not self.is_built:
                Module.total += 1

            self._check_export()

        except Error as e:
            raise Error(f"In module imported from {self.export}:\n{e}")

    def compile(self):
        try:
            for import_module in self.import_modules:
                if not import_module.is_built:
                    import_module.compile()
            if not self.is_built:
                with Logger().prefix(f"compile module [{Module.current}/{Module.total}]: {self.export}") as self.logger:
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
        regex_attr_name   = rf'(?:[\w:]+)'                                               # cmake || gnu::always_inline
        regex_attr_val    = rf'(?:".*?")'                                                # "./dir"
        regex_attr_vals   = rf'(?:{regex_attr_val}?(?:\s*,\s*{regex_attr_val})*)'        # "./dir1", "./dir2"
        regex_attr        = rf'(?:{regex_attr_name}(?:\s*\(\s*{regex_attr_vals}\s*\))?)' # cmake || cmake("./dir")
        regex_attrs       = rf'(?:{regex_attr}?(?:\s*,\s*{regex_attr})*)'                # cmake, autogen, configure
        regex_attr_quote  = rf'(?:\[\[\s*{regex_attrs}\s*\]\])'                          # [[cmake, autogen, configure]]
  
        match_attr_name   = rf'([\w:]+)'
        match_attr_val    = rf'"(.*?)"'
        match_attr        = rf'({regex_attr_name}(?:\s*\(\s*{regex_attr_vals}\s*\))?)'
        match_attr_quote  = rf'(\[\[\s*{regex_attrs}\s*\]\])'

        for attr_quote in   re.findall(match_attr_quote, self.content, flags=re.DOTALL):
            for attr   in   re.findall(match_attr,       attr_quote,   flags=re.DOTALL):
                attr_key  = re.findall(match_attr_name,  attr,         flags=re.DOTALL)[0]
                attr_vals = re.findall(match_attr_val,   attr,         flags=re.DOTALL)
                if attr_key.startswith("anonymous::"):
                    if attr_key == "anonymous::cmake_directory":
                        self._cmake_directory(dir =attr_vals[0], args=attr_vals[1:])
                    elif attr_key == "anonymous::make_directory":
                        self._make_directory (dir =attr_vals[0], args=attr_vals[1:])
                    elif attr_key == "anonymous::shell_configure":
                        self._shell_configure(file=attr_vals[0], args=attr_vals[1:])
                    elif attr_key == "anonymous::perl_configure":
                        self._perl_configure (file=attr_vals[0], args=attr_vals[1:])
                    elif attr_key == "anonymous::update_header":
                        self._update_header  (file=attr_vals[0], args=attr_vals[1:])
                    elif attr_key == "anonymous::update_library":
                        self._update_library (file=attr_vals[0], args=attr_vals[1:])
                    else:
                        raise Error(f"error: unknown module attribute [[{attr_key}]]")
                    
    def _run_subbuild(self, command, **kwargs):
        proc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, **kwargs)
        stderr = ""

        def read_stdout():
            while proc.poll() is None:
                self.logger.suffix(proc.stdout.readline().removesuffix('\n'))
        
        def read_stderr():
            nonlocal stderr
            while proc.poll() is None:
                stderr += proc.stderr.readline()

        stdout_thread = threading.Thread(target=read_stdout)
        stderr_thread = threading.Thread(target=read_stderr)
        stdout_thread.start()
        stderr_thread.start()
        stdout_thread.join()
        stderr_thread.join()

        if proc.returncode != 0:
            raise Error(stderr)
                    
    def _cmake_directory(self, dir, args):
        try:
            os.mkdir(f"./bin/{type}/cmake/{self.export}-build")
            os.mkdir(f"./bin/{type}/cmake/{self.export}-install")
        except:
            pass
        self._run_subbuild(f"cmake -S {dir} -B ./bin/{type}/cmake/{self.export}-build "
                           f"--install-prefix={os.path.abspath(f"./bin/{type}/cmake/{self.export}-install")} "
                           f"-DCMAKE_BUILD_TYPE={type.capitalize()} {' '.join(args)}")
        self._run_subbuild(f"cmake --build   ./bin/{type}/cmake/{self.export}-build")
        self._run_subbuild(f"cmake --install ./bin/{type}/cmake/{self.export}-build")


    def _make_directory(self, dir, args):
        try:
            os.mkdir(f"./bin/{type}/cmake/{self.export}-build")
            os.mkdir(f"./bin/{type}/cmake/{self.export}-install")
        except:
            pass
        self._run_subbuild(f"make BUILD_TYPE={type.capitalize()}", cwd=f"./bin/{type}/cmake/{self.export}-build")
        self._run_subbuild(f"make install",                        cwd=f"./bin/{type}/cmake/{self.export}-build")

    def _shell_configure(self, file, args):
        try:
            os.mkdir(f"./bin/{type}/cmake/{self.export}-build")
        except:
            pass
        self._run_subbuild(f"{os.path.abspath(file)} --prefix={os.path.abspath(f"./bin/{type}/cmake/{self.export}-install")}", cwd=f"./bin/{type}/cmake/{self.export}-build")
    
    def _perl_configure(self, file, args):
        try:
            os.mkdir(f"./bin/{type}/cmake/{self.export}-build")
        except:
            pass
        self._run_subbuild(f"perl {os.path.abspath(file)} --prefix={os.path.abspath(f"./bin/{type}/cmake/{self.export}-install")} --{type}", cwd=f"./bin/{type}/cmake/{self.export}-build")
        
    def _update_header(self, file, args):
        if not file.startswith("<") or not file.endswith(">"):
            raise Error("error: module attribute [[anonymous::update_header]] accepts an argument with <> quoted")
        try:
            shutil.copyfile(f"./bin/{type}/cmake/{self.export}-install/include/{file.strip("<>")}", f"./lib/include/{file.strip("<>")}")
        except FileNotFoundError as e:
            raise Error(f"error: header {file} not found and not updated")
        
    def _update_library(self, file, args):
        try:
            if '.' in file:
                shutil.copyfile(f"./bin/{type}/cmake/{self.export}-install/lib/{file}",                 f"./bin/{type}/module/{file}"                )
            else:
                shutil.copyfile(f"./bin/{type}/cmake/{self.export}-install/lib/{file}{library_suffix}", f"./bin/{type}/module/{file}{library_suffix}")
        except Exception as e:
            raise Error(f"error: library {file} not found and not updated")


class Binary:
    def __init__(self, executable):
        self.executable = executable

    def link(self):
        print(f"link binary [1/1]: {self.executable}")
        link(executable_path=f"./bin/{self.executable}{executable_suffix}")

class Logger:
    def prefix(self, prefix_str):
        self.prefix_str = prefix_str
        return self

    def suffix(self, suffix_str):
        print(f"\r{self.prefix_str} {suffix_str}".replace('\t', ' ').ljust(os.get_terminal_size().columns)[:os.get_terminal_size().columns], end="")
        return self

    def __enter__(self):
        print(f"\r{self.prefix_str}"             .replace('\t', ' ').ljust(os.get_terminal_size().columns)[:os.get_terminal_size().columns], end="")
        return self

    def __exit__(self, *args, **kwargs):
        print(f"\r{self.prefix_str}"             .replace('\t', ' ').ljust(os.get_terminal_size().columns)[:os.get_terminal_size().columns], end="")
        print()
        
        
        
            





# Main

if __name__ == "__main__":
    try:
        parser = argparse.ArgumentParser(description="build.py")
        parser.add_argument("--type",  choices=["debug", "release"], default="debug")
        parser.add_argument("--clean", action="store_true")

        try:
            args = parser.parse_args()
        except argparse.ArgumentError:
            raise Error("Usage: [--type {debug,release}] [--clean]")
        

        if not args.clean:
            type = args.type
            Module("main").compile()
            Binary("main").link()

        else:
            for dir in os.listdir (f"./bin/{type}/cmake"):
                shutil.rmtree     (f"./bin/{type}/cmake/{dir}")
            for file in os.listdir(f"./bin/{type}/module"):
                os.remove         (f"./bin/{type}/module/{file}")
    
    except Error as e:
        print(e, file=sys.stderr)
        print(e, file=open(f"./bin/log.txt", 'w'))
        exit(-1)

    except KeyboardInterrupt as e:
        exit(-1)
