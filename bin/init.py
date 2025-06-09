import os
import shutil

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
shutil.copytree("./git/cccl/libcudacxx/include/cuda", "./include/cuda",            dirs_exist_ok=True)
shutil.copytree("./git/cccl/libcudacxx/include/nv",   "./include/nv",              dirs_exist_ok=True)
shutil.copytree("./git/cccl/thrust/thrust",           "./include/thrust",          dirs_exist_ok=True)
shutil.copytree("./git/eigen/Eigen",                  "./include/Eigen",           dirs_exist_ok=True)
shutil.copyfile("./git/hwloc/include/hwloc.h",        "./include/hwloc.h"                            )
shutil.copytree("./git/hwloc/include/hwloc",          "./include/hwloc",           dirs_exist_ok=True)
shutil.copytree("./git/hwloc/include/private",        "./include/private",         dirs_exist_ok=True)
shutil.copytree("./git/hwloc/hwloc",                  "./include/hwloc",           dirs_exist_ok=True)
shutil.copytree("./git/oneTBB/include/oneapi",        "./include/oneapi",          dirs_exist_ok=True)
shutil.copytree("./git/oneTBB/include/tbb",           "./include/tbb",             dirs_exist_ok=True)
shutil.copytree("./git/oneTBB/src/tbb",               "./include/tbb",             dirs_exist_ok=True)
shutil.copytree("./git/oneTBB/src/tbbbind",           "./include/tbbbind",         dirs_exist_ok=True)
shutil.copytree("./git/oneTBB/src/tbbmalloc",         "./include/tbbmalloc",       dirs_exist_ok=True)
shutil.copytree("./git/oneTBB/src/tbbmalloc_proxy",   "./include/tbbmalloc_proxy", dirs_exist_ok=True)
shutil.copytree("./git/openssl/include/crypto",       "./include/crypto",          dirs_exist_ok=True)
shutil.copytree("./git/openssl/include/openssl",      "./include/openssl",         dirs_exist_ok=True)
shutil.copytree("./git/openssl/include/internal",     "./include/internal",        dirs_exist_ok=True)
shutil.copytree("./git/openssl/crypto",               "./include/crypto",          dirs_exist_ok=True)
shutil.copytree("./git/openssl/ssl",                  "./include/ssl",             dirs_exist_ok=True)
shutil.copyfile("./git/plf_hive/plf_hive.h",          "./include/plf_hive.h"                         )
shutil.copytree("./git/stdexec/include/asioexec",     "./include/asioexec",        dirs_exist_ok=True)
shutil.copytree("./git/stdexec/include/exec",         "./include/exec",            dirs_exist_ok=True)
shutil.copytree("./git/stdexec/include/execpools",    "./include/execpools",       dirs_exist_ok=True)
shutil.copytree("./git/stdexec/include/nvexec",       "./include/nvexec",          dirs_exist_ok=True)
shutil.copytree("./git/stdexec/include/stdexec",      "./include/stdexec",         dirs_exist_ok=True)
shutil.copytree("./git/stdexec/include/tbbexec",      "./include/tbbexec",         dirs_exist_ok=True)

for lib in os.listdir  ( "./git/boost/libs"):
    if os.path.isdir   (f"./git/boost/libs/{lib}/include/boost"):
        shutil.copytree(f"./git/boost/libs/{lib}/include/boost", f"./include/boost", dirs_exist_ok=True)
    if os.path.isdir   (f"./git/boost/libs/{lib}/src"):
        shutil.copytree(f"./git/boost/libs/{lib}/src",           f"./include/boost", dirs_exist_ok=True)