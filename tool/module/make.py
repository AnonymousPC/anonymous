from module.config import *
from module.run import *

def cmake(export_name, dir, args=[]):
    run(f"cmake -S ./{dir} "
        f"      -B ./bin/{type}/third_party/build/{export_name} "
        f"      -DCMAKE_PREFIX_PATH=./bin/{type}/third_party/install "
        f"      -DCMAKE_INSTALL_PREFIX=./bin/{type}/third_party/install "
        f"      -DCMAKE_BUILD_TYPE={type} "
        f"{' '.join(args)}")
    run(f"cmake --build   ./bin/{type}/third_party/build/{export_name} -j1") # TODO: -j
    run(f"cmake --install ./bin/{type}/third_party/build/{export_name}")

def autogen(export_name, file, args=[]):
    cwd = f"./bin/{type}/third_party/build/{export_name}"
    try: os.mkdir(cwd)
    except: pass
    run(f"sh {os.path.relpath(file, cwd)} {' '.join(args)}", cwd=cwd)

def perl(export_name, file, args=[]):
    cwd = f"./bin/{type}/third_party/build/{export_name}"
    try: os.mkdir(cwd)
    except: pass
    run(f"perl {os.path.relpath(file, cwd)} --prefix={os.path.abspath(f"./bin/{type}/third_party/install")} {' '.join(args)}", cwd=cwd)

def configure(export_name, file, args=[]):
    cwd = f"./bin/{type}/third_party/build/{export_name}"
    try: os.mkdir(cwd)
    except: pass
    run(f"sh {os.path.relpath(file, cwd)} --prefix={os.path.abspath(f"./bin/{type}/third_party/install")} {' '.join(args)}", cwd=cwd)

def make(export_name, dir, args=[]):
    cwd = f"./bin/{type}/third_party/build/{export_name}"
    try: os.mkdir(cwd)
    except: pass
    run(f"make -j {' '.join(args)}", cwd=cwd)
    run(f"make install",             cwd=cwd)
