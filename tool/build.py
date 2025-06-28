import sys
sys.dont_write_bytecode = True
from common.module import *
from common.binary import *

if __name__ == "__main__":
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