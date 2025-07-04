import shutil
from module.config import *

shutil.copytree("./package/oneTBB/include",             f"./bin/{type}/package/install/include",                         dirs_exist_ok=True)
shutil.copytree("./package/oneTBB/src/tbb",             f"./bin/{type}/package/install/include/tbb/src/tbb",             dirs_exist_ok=True)
shutil.copytree("./package/oneTBB/src/tbbbind",         f"./bin/{type}/package/install/include/tbb/src/tbbbind",         dirs_exist_ok=True)
shutil.copytree("./package/oneTBB/src/tbbmalloc",       f"./bin/{type}/package/install/include/tbb/src/tbbmalloc",       dirs_exist_ok=True)
shutil.copytree("./package/oneTBB/src/tbbmalloc_proxy", f"./bin/{type}/package/install/include/tbb/src/tbbmalloc_proxy", dirs_exist_ok=True)
