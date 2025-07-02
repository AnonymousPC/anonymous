import shutil
from module.config import *

shutil.copytree("./third_party/eigen/Eigen",       f"./bin/{type}/third_party/install/include/Eigen",       dirs_exist_ok=True)
shutil.copytree("./third_party/eigen/unsupported", f"./bin/{type}/third_party/install/include/unsupported", dirs_exist_ok=True)