from module.compiler import *
from module.config   import *
from module.run      import *

def cmake(name, dir, args=[]):
    if not os.path.isdir(f"./bin/{type}/package/build/{name}"):
        run(f"cmake -S ./{dir} "
            f"      -B ./bin/{type}/package/build/{name} "
            f"      -DCMAKE_PREFIX_PATH=./bin/{type}/package/install "
            f"      -DCMAKE_INSTALL_PREFIX=./bin/{type}/package/install "
            f"      -DCMAKE_BUILD_TYPE={type} "
            f"{' '.join(args)}")
    run(f"cmake --build   ./bin/{type}/package/build/{name} -j{os.cpu_count()}", quiet=True)
    run(f"cmake --install ./bin/{type}/package/build/{name}")

def autogen(name, file, args=[]):
    if not os.path.isdir(f"./bin/{type}/package/build/{name}"):
        run(f"./{file} {' '.join(args)}")

def configure(name, file, args=[]):
    if not os.path.isdir(f"./bin/{type}/package/build/{name}"):
        cwd = f"./bin/{type}/package/build/{name}"
        try: os.mkdir(cwd)
        except: pass
        run(f"./{os.path.relpath(file, cwd)} --prefix={os.path.abspath(f"./bin/{type}/package/install")} {' '.join(args)}", cwd=cwd)

def make(name, dir, args=[]):
    cwd = f"./bin/{type}/package/build/{name}"
    try: os.mkdir(cwd)
    except: pass
    if system == "windows":
        run(f"nmake -j{os.cpu_count()} {' '.join(args)}", cwd=cwd, quiet=True)
        run(f"nmake install",                             cwd=cwd, quiet=True)
    elif system == "linux" or system == "macos":
        run(f"make -j{os.cpu_count()} {' '.join(args)}", cwd=cwd, quiet=True)
        run(f"make install",                             cwd=cwd, quiet=True)

def archieve(name, libs):
    archieved = False
    for libdir in os.listdir(f"./bin/{type}/package/install"):
        if "lib" in libdir:
            if all(os.path.isfile(f"./bin/{type}/package/install/{libdir}/{lib}.{library_suffix}") for lib in libs):
                archieve_libraries(library_files=[f"./bin/{type}/package/install/{libdir}/{lib}.{library_suffix}" for lib in libs], archieve_file=f"./bin/{type}/module/{name}.{library_suffix}")
                archieved = True
                break
    if not archieved:
        raise Exception(f"fatal error: libraries {' '.join(libs)} not found and not archieved")