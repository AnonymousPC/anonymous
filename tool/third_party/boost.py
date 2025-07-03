import os
import shutil
from module.config import *

for lib in os.listdir  ( "./third_party/boost/libs"):
    if os.path.isdir   (f"./third_party/boost/libs/{lib}/include"):
        shutil.copytree(f"./third_party/boost/libs/{lib}/include",         f"./bin/{type}/third_party/install/include",                         dirs_exist_ok=True)
    if os.path.isdir   (f"./third_party/boost/libs/{lib}/src"):
        shutil.copytree(f"./third_party/boost/libs/{lib}/src",             f"./bin/{type}/third_party/install/include/boost/{lib}/src",         dirs_exist_ok=True)

for lib in os.listdir  ( "./third_party/boost/libs/numeric"):
    if os.path.isdir   (f"./third_party/boost/libs/numeric/{lib}/include"):
        shutil.copytree(f"./third_party/boost/libs/numeric/{lib}/include", f"./bin/{type}/third_party/install/include",                         dirs_exist_ok=True)
    if os.path.isdir   (f"./third_party/boost/libs/numeric/{lib}/src"):
        shutil.copytree(f"./third_party/boost/libs/numeric/{lib}/src",     f"./bin/{type}/third_party/install/include/boost/numeric/{lib}/src", dirs_exist_ok=True)