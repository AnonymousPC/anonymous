import shutil
from module.config import *

shutil.copytree("./package/cccl/libcudacxx/include", f"./bin/{type}/package/install/include",        dirs_exist_ok=True)
shutil.copytree("./package/cccl/thrust/thrust",      f"./bin/{type}/package/install/include/thrust", dirs_exist_ok=True)