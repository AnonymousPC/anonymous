import shutil
from module.config import *

shutil.copytree("./third_party/stdexec/include", f"./bin/{type}/third_party/install/include", dirs_exist_ok=True)