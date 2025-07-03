from module.config import *
import shutil

try: 
    shutil.rmtree(f"./bin/{type}")
except:
    pass