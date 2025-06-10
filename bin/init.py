import os
import shutil
import build

# Environment
os.chdir(f"{os.path.dirname(__file__)}/../lib")



# Clean
try:
    shutil.rmtree("./include")
except FileNotFoundError:
    pass
os.mkdir("./include")
open("./include/.gitignore", 'w').write("*\n!.gitignore")




# Copy
shutil.copytree("./git/c++/cccl/libcudacxx/include/cuda", "./include/cuda",            dirs_exist_ok=True)
shutil.copytree("./git/c++/cccl/libcudacxx/include/nv",   "./include/nv",              dirs_exist_ok=True)
shutil.copytree("./git/c++/cccl/thrust/thrust",           "./include/thrust",          dirs_exist_ok=True)
shutil.copytree("./git/c++/eigen/Eigen",                  "./include/Eigen",           dirs_exist_ok=True)
shutil.copytree("./git/c++/oneTBB/include/oneapi",        "./include/oneapi",          dirs_exist_ok=True)
shutil.copytree("./git/c++/oneTBB/include/tbb",           "./include/tbb",             dirs_exist_ok=True)
shutil.copytree("./git/c++/oneTBB/src/tbb",               "./include/tbb",             dirs_exist_ok=True)
shutil.copytree("./git/c++/oneTBB/src/tbbbind",           "./include/tbbbind",         dirs_exist_ok=True)
shutil.copytree("./git/c++/oneTBB/src/tbbmalloc",         "./include/tbbmalloc",       dirs_exist_ok=True)
shutil.copytree("./git/c++/oneTBB/src/tbbmalloc_proxy",   "./include/tbbmalloc_proxy", dirs_exist_ok=True)
shutil.copyfile("./git/c++/plf_hive/plf_hive.h",          "./include/plf_hive.h"                         )
shutil.copytree("./git/c++/stdexec/include/asioexec",     "./include/asioexec",        dirs_exist_ok=True)
shutil.copytree("./git/c++/stdexec/include/exec",         "./include/exec",            dirs_exist_ok=True)
shutil.copytree("./git/c++/stdexec/include/execpools",    "./include/execpools",       dirs_exist_ok=True)
shutil.copytree("./git/c++/stdexec/include/nvexec",       "./include/nvexec",          dirs_exist_ok=True)
shutil.copytree("./git/c++/stdexec/include/stdexec",      "./include/stdexec",         dirs_exist_ok=True)
shutil.copytree("./git/c++/stdexec/include/tbbexec",      "./include/tbbexec",         dirs_exist_ok=True)

for lib in os.listdir  ( "./git/c++/boost/libs"):
    if os.path.isdir   (f"./git/c++/boost/libs/{lib}/include/boost"):
        shutil.copytree(f"./git/c++/boost/libs/{lib}/include/boost", f"./include/boost", dirs_exist_ok=True)
    if os.path.isdir   (f"./git/c++/boost/libs/{lib}/src"):
        shutil.copytree(f"./git/c++/boost/libs/{lib}/src",           f"./include/boost", dirs_exist_ok=True)

for root, _, files in os.walk("./include"):
    for file in files:
        if file.endswith(".in"):
            shutil.copyfile(f"{root}/{file}", f"{root}/{file.removesuffix(".in")}")