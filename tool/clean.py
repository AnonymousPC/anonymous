import sys
sys.dont_write_bytecode = True
from module.config import *
import shutil

try: 
    shutil.rmtree(f"./bin/{type}")
except:
    pass