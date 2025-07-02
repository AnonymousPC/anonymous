import shutil
from module.config import *

shutil.copytree("./third_party/cccl/libcudacxx/include", f"./bin/{type}/third_party/install/include",        dirs_exist_ok=True)
shutil.copytree("./third_party/cccl/thrust/thrust",      f"./bin/{type}/third_party/install/include/thrust", dirs_exist_ok=True)