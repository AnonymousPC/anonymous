import os
import shutil
from build import *

# Environment
os.chdir(f"{os.path.dirname(__file__)}/..")



# Clean
try:
    shutil.rmtree("./lib/include")
except FileNotFoundError:
    pass
os.mkdir("./lib/include")
open("./lib/include/.gitignore", 'w').write("*\n!.gitignore")




# C++
for lib in os.listdir  ( "./lib/git/c++/boost/libs"):
    if os.path.isdir   (f"./lib/git/c++/boost/libs/{lib}/include/boost"):
        shutil.copytree(f"./lib/git/c++/boost/libs/{lib}/include/boost", f"./lib/include/boost",           dirs_exist_ok=True)
    if os.path.isdir   (f"./lib/git/c++/boost/libs/{lib}/src"):
        shutil.copytree(f"./lib/git/c++/boost/libs/{lib}/src",           f"./lib/include/boost/{lib}/src", dirs_exist_ok=True)

shutil.copytree("./lib/git/c++/cccl/libcudacxx/include/cuda", "./lib/include/cuda",                    dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/cccl/libcudacxx/include/nv",   "./lib/include/nv",                      dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/cccl/thrust/thrust",           "./lib/include/thrust",                  dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/eigen/Eigen",                  "./lib/include/Eigen",                   dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/oneTBB/include/tbb",           "./lib/include/tbb",                     dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/oneTBB/src/tbb",               "./lib/include/tbb/src/tbb",             dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/oneTBB/src/tbbbind",           "./lib/include/tbb/src/tbbbind",         dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/oneTBB/src/tbbmalloc",         "./lib/include/tbb/src/tbbmalloc",       dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/oneTBB/src/tbbmalloc_proxy",   "./lib/include/tbb/src/tbbmalloc_proxy", dirs_exist_ok=True)
shutil.copyfile("./lib/git/c++/plf_hive/plf_hive.h",          "./lib/include/plf_hive.h"                                 )
shutil.copytree("./lib/git/c++/stdexec/include/asioexec",     "./lib/include/asioexec",                dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/stdexec/include/exec",         "./lib/include/exec",                    dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/stdexec/include/execpools",    "./lib/include/execpools",               dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/stdexec/include/nvexec",       "./lib/include/nvexec",                  dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/stdexec/include/stdexec",      "./lib/include/stdexec",                 dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/stdexec/include/tbbexec",      "./lib/include/tbbexec",                 dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/xlnt/include/xlnt",            "./lib/include/xlnt",                    dirs_exist_ok=True)
shutil.copytree("./lib/git/c++/xlnt/source",                  "./lib/include/xlnt/src",                dirs_exist_ok=True)


# C
Library("bzip2").cmake()
shutil.copyfile("./lib/git/c/bzip2/bzlib.h", "./lib/include/bzlib.h")
Library("hwloc").cmake()
shutil.copyfile("./lib/git/c/hwloc/include/hwloc.h", "./lib/include/hwloc")
shutil.copytree("./lib/git/c/hwloc/include/hwloc",   "./lib/include/hwloc.h")
Library("icu").cmake()
