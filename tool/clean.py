from module.config import *
from module.init   import *
import shutil

if __name__ == "__main__":
    try:  shutil.rmtree(f"./bin/{type}")
    except: pass