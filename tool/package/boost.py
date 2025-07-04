import os
import shutil
from module.config import *

for lib in os.listdir  ( "./package/boost/libs"):
    if os.path.isdir   (f"./package/boost/libs/{lib}/include"):
        shutil.copytree(f"./package/boost/libs/{lib}/include",         f"./bin/{type}/package/install/include",                         dirs_exist_ok=True)
    if os.path.isdir   (f"./package/boost/libs/{lib}/src"):
        shutil.copytree(f"./package/boost/libs/{lib}/src",             f"./bin/{type}/package/install/include/boost/{lib}/src",         dirs_exist_ok=True)

for lib in os.listdir  ( "./package/boost/libs/numeric"):
    if os.path.isdir   (f"./package/boost/libs/numeric/{lib}/include"):
        shutil.copytree(f"./package/boost/libs/numeric/{lib}/include", f"./bin/{type}/package/install/include",                         dirs_exist_ok=True)
    if os.path.isdir   (f"./package/boost/libs/numeric/{lib}/src"):
        shutil.copytree(f"./package/boost/libs/numeric/{lib}/src",     f"./bin/{type}/package/install/include/boost/numeric/{lib}/src", dirs_exist_ok=True)