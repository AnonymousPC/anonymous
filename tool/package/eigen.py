import shutil
from module.config import *

shutil.copytree("./package/eigen/Eigen",       f"./bin/{type}/package/install/include/Eigen",       dirs_exist_ok=True)
shutil.copytree("./package/eigen/unsupported", f"./bin/{type}/package/install/include/unsupported", dirs_exist_ok=True)