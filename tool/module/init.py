from module.config   import *
from module.compiler import *

def try_write_file(file):
    try:
        open(file, 'w')
    except FileNotFoundError:
        pass

def try_mkdir(dir):
    try:
        os.mkdir(dir)
    except FileExistsError:
        pass

try_mkdir(f"./bin/{type}")
try_mkdir(f"./bin/{type}/module")
try_mkdir(f"./bin/{type}/package")
try_mkdir(f"./bin/{type}/package/build")
try_mkdir(f"./bin/{type}/package/install")
try_mkdir(f"./bin/{type}/package/install/include")
try_mkdir(f"./bin/{type}/package/install/lib")
if compiler == "g++":
    try_write_file(f"./bin/{type}/module/mapper.txt")