import shutil
from module.config import *

shutil.copytree("./third_party/oneTBB/include",             f"./bin/{type}/third_party/install/include",                         dirs_exist_ok=True)
shutil.copytree("./third_party/oneTBB/src/tbb",             f"./bin/{type}/third_party/install/include/tbb/src/tbb",             dirs_exist_ok=True)
shutil.copytree("./third_party/oneTBB/src/tbbbind",         f"./bin/{type}/third_party/install/include/tbb/src/tbbbind",         dirs_exist_ok=True)
shutil.copytree("./third_party/oneTBB/src/tbbmalloc",       f"./bin/{type}/third_party/install/include/tbb/src/tbbmalloc",       dirs_exist_ok=True)
shutil.copytree("./third_party/oneTBB/src/tbbmalloc_proxy", f"./bin/{type}/third_party/install/include/tbb/src/tbbmalloc_proxy", dirs_exist_ok=True)
