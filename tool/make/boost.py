from ..common.cmake import *

cmake_file(
    file="./third_party/git/boost/CMakeLists.txt",
)

for lib in os.listdir              (f"./third_party/git/boost/libs"):
    if os.path.isdir               (f"./third_party/git/boost/libs/{lib}"):
        if os.path.isdir           (f"./third_party/git/boost/libs/{lib}/include/boost"):
            install_include        (f"./third_party/git/boost/libs/{lib}/include")
        else:
            for sub in os.listdir  (f"./third_party/git/boost/libs/{lib}"):
                if os.path.isdir   (f"./third_party/git/boost/libs/{lib}/{sub}/include/boost"):
                    install_include(f"./third_party/git/boost/libs/{lib}/{sub}/include")

        if os.path.isdir           (f"./third_party/git/boost/libs/{lib}/src"):
            shutil.copytree        (f"./third_party/git/boost/libs/{lib}/src",                 f"./third_party/include/boost/{lib}/src",       dirs_exist_ok=True)
        else:
            for sub in os.listdir  (f"./third_party/git/boost/libs/{lib}"):
                if os.path.isdir   (f"./third_party/git/boost/libs/{lib}/{sub}/src"):
                    shutil.copytree(f"./third_party/git/boost/libs/{lib}/{sub}/src",           f"./third_party/include/boost/{lib}/{sub}/src", dirs_exist_ok=True)