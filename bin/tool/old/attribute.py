import os
import re
import shutil
import subprocess
import threading
from config import *
from progress_bar import *

def apply_attribute(module):
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

    for attr_quote in   re.findall(match_attr_quote, module.content, flags=re.DOTALL):
        for attr   in   re.findall(match_attr,       attr_quote,     flags=re.DOTALL):
            attr_key  = re.findall(match_attr_name,  attr,           flags=re.DOTALL)[0]
            attr_vals = re.findall(match_attr_val,   attr,           flags=re.DOTALL)
            if attr_key.startswith("anonymous::"):
                if attr_key == "anonymous::cmake_directory":
                    _cmake_directory(module=module, dir =attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::make_directory":
                    _make_directory (module=module, dir =attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::autogen_file":
                    _autogen_file   (module=module, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::configure_file":
                    _configure_file (module=module, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::perl_file":
                    _perl_file      (module=module, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::update_header":
                    _update_header  (module=module, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::update_library":
                    _update_library (module=module, file=attr_vals[0], args=attr_vals[1:])
                else:
                    raise Exception(f"error: unknown module attribute [[{attr_key}]]")
                



# detail

_compile_env = os.environ.copy()
_compile_env["CC"]       = c_compiler
_compile_env["CXX"]      = compiler
_compile_env["CFLAGS"]   = ' '.join(c_compile_args)
_compile_env["CXXFLAGS"] = ' '.join(compile_args)

def _run_command(command, **kwargs):
    proc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, **kwargs)
    stderr = ""

    def read_stdout():
        while proc.poll() is None:
            progress_bar.suffix(proc.stdout.readline().removesuffix('\n'))
    
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

    if proc.returncode == 0:
        if stderr != "":
            print(stderr, end="", file=sys.stderr)
    else:
        raise Exception(stderr)
                
def _cmake_directory(module, dir, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{module.export_name}-build")
        os.mkdir(f"./bin/{type}/cmake/{module.export_name}-install")
    except:
        pass
    _run_command(f"cmake --install-prefix={os.path.abspath(f"./bin/{type}/cmake/{module.export_name}-install")} -DCMAKE_BUILD_TYPE={type.capitalize()} {' '.join(args)} -S ./{dir} -B ./bin/{type}/cmake/{module.export_name}-build", env=_compile_env)
    _run_command(f"cmake --build   ./bin/{type}/cmake/{module.export_name}-build  -j{os.cpu_count()}")
    _run_command(f"cmake --install ./bin/{type}/cmake/{module.export_name}-build")


def _make_directory(module, dir, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{module.export_name}-build")
        os.mkdir(f"./bin/{type}/cmake/{module.export_name}-install")
    except:
        pass
    _run_command(f"make -j{os.cpu_count()}", cwd=f"./bin/{type}/cmake/{module.export_name}-build")
    _run_command(f"make install",            cwd=f"./bin/{type}/cmake/{module.export_name}-build")

def _autogen_file(module, file, args):
    _run_command(f"sh ./autogen.sh", cwd=file.rpartition('/')[0])

def _configure_file(module, file, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{module.export_name}-build")
    except:
        pass
    _run_command(f"sh {os.path.abspath(file)} --prefix={os.path.abspath(f"./bin/{type}/cmake/{module.export_name}-install")}", cwd=f"./bin/{type}/cmake/{module.export_name}-build", env=_compile_env)

def _perl_file(module, file, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{module.export_name}-build")
    except:
        pass
    _run_command(f"perl {os.path.abspath(file)} --prefix={os.path.abspath(f"./bin/{type}/cmake/{module.export_name}-install")} --{type}", cwd=f"./bin/{type}/cmake/{module.export_name}-build")
    
def _update_header(module, file, args):
    if not file.startswith("<") or not file.endswith(">"):
        raise Exception("error: module attribute [[anonymous::update_header]] accepts an argument with <> quoted")
    try:
        shutil.copyfile(f"./bin/{type}/cmake/{module.export_name}-install/include/{file.strip("<>")}", f"./third_party/include/{file.strip("<>")}")
    except FileNotFoundError as e:
        raise Exception(f"error: header {file} not found and not updated")
    
def _update_library(module, file, args):
    try:
        if '.' in file:
            shutil.copyfile(f"./bin/{type}/cmake/{module.export_name}-install/lib/{file}",                 f"./bin/{type}/module/{file}"                )
        else:
            shutil.copyfile(f"./bin/{type}/cmake/{module.export_name}-install/lib/{file}{library_suffix}", f"./bin/{type}/module/{file}{library_suffix}")
    except Exception as e:
        raise Exception(f"error: library {file} not found and not updated")
    



            
