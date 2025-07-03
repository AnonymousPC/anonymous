from module.config import *
from module.run   import *

def cmake(module_name, dir, args=[]):
    if not os.path.isdir(f"./bin/{type}/third_party/build/{module_name}"):
        run(f"cmake -S ./{dir} "
            f"      -B ./bin/{type}/third_party/build/{module_name} "
            f"      -DCMAKE_PREFIX_PATH=./bin/{type}/third_party/install "
            f"      -DCMAKE_INSTALL_PREFIX=./bin/{type}/third_party/install "
            f"      -DCMAKE_BUILD_TYPE={type} "
            f"{' '.join(args)}")
    run(f"cmake --build   ./bin/{type}/third_party/build/{module_name} -j{os.cpu_count()}", quiet=True)
    run(f"cmake --install ./bin/{type}/third_party/build/{module_name}")

def autogen(module_name, file, args=[]):
    if not os.path.isdir(f"./bin/{type}/third_party/build/{module_name}"):
        run(f"./{file} {' '.join(args)}")

def configure(module_name, file, args=[]):
    if not os.path.isdir(f"./bin/{type}/third_party/build/{module_name}"):
        cwd = f"./bin/{type}/third_party/build/{module_name}"
        try: os.mkdir(cwd)
        except: pass
        run(f"./{os.path.relpath(file, cwd)} --prefix={os.path.abspath(f"./bin/{type}/third_party/install")} {' '.join(args)}", cwd=cwd)

def make(module_name, dir, args=[]):
    cwd = f"./bin/{type}/third_party/build/{module_name}"
    try: os.mkdir(cwd)
    except: pass
    if system == "windows":
        run(f"nmake -j{os.cpu_count()} {' '.join(args)}", cwd=cwd, quiet=True)
        run(f"nmake install",                             cwd=cwd, quiet=True)
    elif system == "linux" or system == "macos":
        run(f"make -j{os.cpu_count()} {' '.join(args)}", cwd=cwd, quiet=True)
        run(f"make install",                             cwd=cwd, quiet=True)
