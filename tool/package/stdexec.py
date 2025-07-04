import shutil
from module.config import *

shutil.copytree("./package/stdexec/include", f"./bin/{type}/package/install/include", dirs_exist_ok=True)