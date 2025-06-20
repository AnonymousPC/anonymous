import sys
sys.dont_write_bytecode = True

from module import *
from binary import *

if __name__ == "__main__":

    # Environment
    os.chdir(f"{os.path.dirname(__file__)}/../..")
    sys.dont_write_bytecode = True

    # Build
    try:
        Module("main").compile()
        Binary("main").link()
    except Exception as e:
        print(e, end="", file=sys.stderr)
        print(e, end="", file=open("./bin/log.txt", 'w'))
        exit(-1)
    except KeyboardInterrupt as e:
        exit(-1)
    except:
        raise