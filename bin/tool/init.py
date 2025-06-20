import os
import shutil

# Environment
os.chdir(f"{os.path.dirname(__file__)}/../..")



# Clean
try:
    shutil.rmtree("./third_party/include")
except FileNotFoundError:
    pass
os.mkdir("./third_party/include")


# Copy
for lib in os.listdir              (f"./third_party/git/boost/libs"):
    if os.path.isdir               (f"./third_party/git/boost/libs/{lib}"):
        if os.path.isdir           (f"./third_party/git/boost/libs/{lib}/include/boost"):
            shutil.copytree        (f"./third_party/git/boost/libs/{lib}/include/boost",       f"./third_party/include/boost",                 dirs_exist_ok=True)
        else:
            for sub in os.listdir  (f"./third_party/git/boost/libs/{lib}"):
                if os.path.isdir   (f"./third_party/git/boost/libs/{lib}/{sub}/include/boost"):
                    shutil.copytree(f"./third_party/git/boost/libs/{lib}/{sub}/include/boost", f"./third_party/include/boost",                 dirs_exist_ok=True)
        if os.path.isdir           (f"./third_party/git/boost/libs/{lib}/src"):
            shutil.copytree        (f"./third_party/git/boost/libs/{lib}/src",                 f"./third_party/include/boost/{lib}/src",       dirs_exist_ok=True)
        else:
            for sub in os.listdir  (f"./third_party/git/boost/libs/{lib}"):
                if os.path.isdir   (f"./third_party/git/boost/libs/{lib}/{sub}/src"):
                    shutil.copytree(f"./third_party/git/boost/libs/{lib}/{sub}/src",           f"./third_party/include/boost/{lib}/{sub}/src", dirs_exist_ok=True)
shutil.copyfile("./third_party/git/bzip2/bzlib.h",                   "./third_party/include/bzlib.h"                                    )
shutil.copytree("./third_party/git/cccl/libcudacxx/include/cuda",    "./third_party/include/cuda",                    dirs_exist_ok=True)
shutil.copytree("./third_party/git/cccl/libcudacxx/include/nv",      "./third_party/include/nv",                      dirs_exist_ok=True)
shutil.copytree("./third_party/git/cccl/thrust/thrust",              "./third_party/include/thrust",                  dirs_exist_ok=True)
shutil.copytree("./third_party/git/eigen/Eigen",                     "./third_party/include/Eigen",                   dirs_exist_ok=True)
shutil.copyfile("./third_party/git/hwloc/include/hwloc.h",           "./third_party/include/hwloc.h"                                    )
shutil.copytree("./third_party/git/hwloc/include/hwloc",             "./third_party/include/hwloc",                   dirs_exist_ok=True)
shutil.copytree("./third_party/git/icu/icu4c/source/common/unicode", "./third_party/include/unicode",                 dirs_exist_ok=True)
shutil.copytree("./third_party/git/icu/icu4c/source/i18n/unicode",   "./third_party/include/unicode",                 dirs_exist_ok=True)
shutil.copytree("./third_party/git/icu/icu4c/source/io/unicode",     "./third_party/include/unicode",                 dirs_exist_ok=True)
shutil.copytree("./third_party/git/icu/icu4c/source/common",         "./third_party/include/unicode/src",             dirs_exist_ok=True)
shutil.copytree("./third_party/git/icu/icu4c/source/i18n",           "./third_party/include/unicode/src",             dirs_exist_ok=True)
shutil.copytree("./third_party/git/icu/icu4c/source/io",             "./third_party/include/unicode/src",             dirs_exist_ok=True)
shutil.copyfile("./third_party/git/libjpeg-turbo/src/jpeglib.h",     "./third_party/include/jpeglib.h"                                  )
shutil.copyfile("./third_party/git/libjpeg-turbo/src/jmorecfg.h",    "./third_party/include/jmorecfg.h"                                 )
shutil.copyfile("./third_party/git/libpng/png.h",                    "./third_party/include/png.h"                                      )
shutil.copyfile("./third_party/git/libtiff/libtiff/tiff.h",          "./third_party/include/tiff.h"                                     )
shutil.copytree("./third_party/git/oneTBB/include/tbb",              "./third_party/include/tbb",                     dirs_exist_ok=True)
shutil.copytree("./third_party/git/oneTBB/src/tbb",                  "./third_party/include/tbb/src/tbb",             dirs_exist_ok=True)
shutil.copytree("./third_party/git/oneTBB/src/tbbbind",              "./third_party/include/tbb/src/tbbbind",         dirs_exist_ok=True)
shutil.copytree("./third_party/git/oneTBB/src/tbbmalloc",            "./third_party/include/tbb/src/tbbmalloc",       dirs_exist_ok=True)
shutil.copytree("./third_party/git/oneTBB/src/tbbmalloc_proxy",      "./third_party/include/tbb/src/tbbmalloc_proxy", dirs_exist_ok=True)
shutil.copytree("./third_party/git/openssl/include/crypto",          "./third_party/include/crypto",                  dirs_exist_ok=True)
shutil.copytree("./third_party/git/openssl/include/openssl",         "./third_party/include/openssl",                 dirs_exist_ok=True)
shutil.copyfile("./third_party/git/plf_hive/plf_hive.h",             "./third_party/include/plf_hive.h"                                 )
shutil.copytree("./third_party/git/stdexec/include/asioexec",        "./third_party/include/asioexec",                dirs_exist_ok=True)
shutil.copytree("./third_party/git/stdexec/include/exec",            "./third_party/include/exec",                    dirs_exist_ok=True)
shutil.copytree("./third_party/git/stdexec/include/execpools",       "./third_party/include/execpools",               dirs_exist_ok=True)
shutil.copytree("./third_party/git/stdexec/include/nvexec",          "./third_party/include/nvexec",                  dirs_exist_ok=True)
shutil.copytree("./third_party/git/stdexec/include/stdexec",         "./third_party/include/stdexec",                 dirs_exist_ok=True)
shutil.copytree("./third_party/git/stdexec/include/tbbexec",         "./third_party/include/tbbexec",                 dirs_exist_ok=True)
shutil.copyfile("./third_party/git/xz/src/liblzma/api/lzma.h",       "./third_party/include/lzma.h"                                     )
shutil.copytree("./third_party/git/xz/src/liblzma/api/lzma",         "./third_party/include/lzma",                    dirs_exist_ok=True)
shutil.copyfile("./third_party/git/zlib/zlib.h",                     "./third_party/include/zlib.h"                                     )
shutil.copyfile("./third_party/git/zlib/zconf.h",                    "./third_party/include/zconf.h"                                    )
shutil.copyfile("./third_party/git/zstd/lib/zstd.h",                 "./third_party/include/zstd.h"                                     )
shutil.copyfile("./third_party/git/zstd/lib/zstd_errors.h",          "./third_party/include/zstd_errors.h"                              )