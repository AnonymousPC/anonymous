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




# Copy
for lib in os.listdir  ( "./lib/git/boost/libs"):
    if os.path.isdir   (f"./lib/git/boost/libs/{lib}/include/boost"):
        shutil.copytree(f"./lib/git/boost/libs/{lib}/include/boost", f"./lib/include/boost",           dirs_exist_ok=True)
    if os.path.isdir   (f"./lib/git/boost/libs/{lib}/src"):
        shutil.copytree(f"./lib/git/boost/libs/{lib}/src",           f"./lib/include/boost/{lib}/src", dirs_exist_ok=True)

shutil.copyfile("./lib/git/bzip2/bzlib.h",                   "./lib/include/bzlib.h"                                    )
shutil.copytree("./lib/git/cccl/libcudacxx/include/cuda",    "./lib/include/cuda",                    dirs_exist_ok=True)
shutil.copytree("./lib/git/cccl/libcudacxx/include/nv",      "./lib/include/nv",                      dirs_exist_ok=True)
shutil.copytree("./lib/git/cccl/thrust/thrust",              "./lib/include/thrust",                  dirs_exist_ok=True)
shutil.copytree("./lib/git/eigen/Eigen",                     "./lib/include/Eigen",                   dirs_exist_ok=True)
shutil.copyfile("./lib/git/hwloc/include/hwloc.h",           "./lib/include/hwloc.h"                                    )
shutil.copytree("./lib/git/hwloc/include/hwloc",             "./lib/include/hwloc",                   dirs_exist_ok=True)
shutil.copytree("./lib/git/icu/icu4c/source/common/unicode", "./lib/include/unicode",                 dirs_exist_ok=True)
shutil.copytree("./lib/git/icu/icu4c/source/i18n/unicode",   "./lib/include/unicode",                 dirs_exist_ok=True)
shutil.copytree("./lib/git/icu/icu4c/source/io/unicode",     "./lib/include/unicode",                 dirs_exist_ok=True)
shutil.copyfile("./lib/git/libjpeg-turbo/src/jpeglib.h",     "./lib/include/jpeglib.h"                                  )
shutil.copyfile("./lib/git/libjpeg-turbo/src/jmorecfg.h",    "./lib/include/jmorecfg.h"                                 )
shutil.copyfile("./lib/git/libpng/png.h",                    "./lib/include/png.h"                                      )
shutil.copyfile("./lib/git/libtiff/libtiff/tiff.h",          "./lib/include/tiff.h"                                     )
shutil.copytree("./lib/git/oneTBB/include/tbb",              "./lib/include/tbb",                     dirs_exist_ok=True)
shutil.copytree("./lib/git/oneTBB/src/tbb",                  "./lib/include/tbb/src/tbb",             dirs_exist_ok=True)
shutil.copytree("./lib/git/oneTBB/src/tbbbind",              "./lib/include/tbb/src/tbbbind",         dirs_exist_ok=True)
shutil.copytree("./lib/git/oneTBB/src/tbbmalloc",            "./lib/include/tbb/src/tbbmalloc",       dirs_exist_ok=True)
shutil.copytree("./lib/git/oneTBB/src/tbbmalloc_proxy",      "./lib/include/tbb/src/tbbmalloc_proxy", dirs_exist_ok=True)
shutil.copyfile("./lib/git/plf_hive/plf_hive.h",             "./lib/include/plf_hive.h"                                 )
shutil.copytree("./lib/git/stdexec/include/asioexec",        "./lib/include/asioexec",                dirs_exist_ok=True)
shutil.copytree("./lib/git/stdexec/include/exec",            "./lib/include/exec",                    dirs_exist_ok=True)
shutil.copytree("./lib/git/stdexec/include/execpools",       "./lib/include/execpools",               dirs_exist_ok=True)
shutil.copytree("./lib/git/stdexec/include/nvexec",          "./lib/include/nvexec",                  dirs_exist_ok=True)
shutil.copytree("./lib/git/stdexec/include/stdexec",         "./lib/include/stdexec",                 dirs_exist_ok=True)
shutil.copytree("./lib/git/stdexec/include/tbbexec",         "./lib/include/tbbexec",                 dirs_exist_ok=True)
shutil.copyfile("./lib/git/zlib/zlib.h",                     "./lib/include/zlib.h"                                     )
shutil.copyfile("./lib/git/zlib/zconf.h",                    "./lib/include/zconf.h"                                    )
shutil.copyfile("./lib/git/zstd/lib/zstd.h",                 "./lib/include/zstd.h"                                     )
shutil.copyfile("./lib/git/zstd/lib/zstd_errors.h",          "./lib/include/zstd_errors.h"                              )