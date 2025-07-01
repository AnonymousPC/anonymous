import os
import re
import shutil
from .config import *
from .run import *

def apply_attribute(export_name, content):
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

    for attr_quote in   re.findall(match_attr_quote, content,        flags=re.DOTALL):
        for attr   in   re.findall(match_attr,       attr_quote,     flags=re.DOTALL):
            attr_key  = re.findall(match_attr_name,  attr,           flags=re.DOTALL)[0]
            attr_vals = re.findall(match_attr_val,   attr,           flags=re.DOTALL)
            if attr_key.startswith("anonymous::"):
                if attr_key == "anonymous::cmake_directory":
                    _cmake_directory(export_name=export_name, dir =attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::make_directory":
                    _make_directory (export_name=export_name, dir =attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::autogen_file":
                    _autogen_file   (export_name=export_name, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::configure_file":
                    _configure_file (export_name=export_name, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::perl_file":
                    _perl_file      (export_name=export_name, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::update_header":
                    _update_header  (export_name=export_name, file=attr_vals[0], args=attr_vals[1:])
                elif attr_key == "anonymous::update_library":
                    _update_library (export_name=export_name, file=attr_vals[0], args=attr_vals[1:])
                else:
                    raise Exception(f"error: unknown module attribute [[{attr_key}]]")
                



def _cmake_directory(export_name, dir, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{export_name}-build")
        os.mkdir(f"./bin/{type}/cmake/{export_name}-install")
    except:
        pass
    run(f"cmake -S ./{dir} -B ./bin/{type}/cmake/{export_name}-build --install-prefix={os.path.abspath(f"./bin/{type}/cmake/{export_name}-install")} -DCMAKE_BUILD_TYPE={type.capitalize()} {' '.join(args)}")
    run(f"cmake --build   ./bin/{type}/cmake/{export_name}-build  -j{os.cpu_count()}")
    run(f"cmake --install ./bin/{type}/cmake/{export_name}-build")


def _make_directory(export_name, dir, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{export_name}-build")
        os.mkdir(f"./bin/{type}/cmake/{export_name}-install")
    except:
        pass
    run(f"make -j{os.cpu_count()} {' '.join(args)}", cwd=f"./bin/{type}/cmake/{export_name}-build")
    run(f"make install",                             cwd=f"./bin/{type}/cmake/{export_name}-build")

def _autogen_file(export_name, file, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{export_name}-build")
    except:
        pass
    cwd = f"./bin/{type}/cmake/{export_name}-build"
    run(f"sh {os.path.relpath(file, cwd)} {' '.join(args)}", cwd=cwd)

def _configure_file(export_name, file, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{export_name}-build")
    except:
        pass
    cwd = f"./bin/{type}/cmake/{export_name}-build"
    run(f"sh {os.path.relpath(file, cwd)} --prefix={os.path.abspath(f"./bin/{type}/cmake/{export_name}-install")} {' '.join(args)}", cwd=cwd)

def _perl_file(export_name, file, args):
    try:
        os.mkdir(f"./bin/{type}/cmake/{export_name}-build")
    except:
        pass
    cwd = f"./bin/{type}/cmake/{export_name}-build"
    run(f"perl {os.path.relpath(file, cwd)} --prefix={os.path.abspath(f"./bin/{type}/cmake/{export_name}-install")} {' '.join(args)}", cwd=cwd)
    
def _update_header(export_name, file, args):
    try:
        if len(args) == 0:
            shutil.copyfile(f"./bin/{type}/cmake/{export_name}-install/include/{file}", f"./third_party/include/{file}")
        elif len(args) == 1:
            shutil.copyfile(f"./bin/{type}/cmake/{export_name}-install/include/{file}", f"./third_party/include/{args[0]}")
        else:
            raise Exception("attribute [[anonymous::update_header(...)]] accepts 1 or 2 arguments")
    except FileNotFoundError as e:
        raise Exception(f"error: header {file} not found and not updated")
    
def _update_library(export_name, file, args):
    try:
        for dir in os.listdir(f"./bin/{type}/cmake/{export_name}-install"):
            if dir.startswith("lib"):
                if len(args) == 0:
                    shutil.copyfile(f"./bin/{type}/cmake/{export_name}-install/{dir}/{file}.{library_suffix}", f"./bin/{type}/module/{file}.{library_suffix}")
                elif len(args) == 1:
                    shutil.copyfile(f"./bin/{type}/cmake/{export_name}-install/{dir}/{file}.{library_suffix}", f"./bin/{type}/module/{args[0]}.{library_suffix}")
                else:
                    raise Exception("attribute [[anonymous::update_library(...)]] accepts 1 or 2 arguments")
    except Exception as e:
        raise Exception(f"error: library {file} not found and not updated")
    



            
