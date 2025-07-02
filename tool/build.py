import sys
sys.dont_write_bytecode = True
from module.source import *
from module.object import *
from module.init   import *


if __name__ == "__main__":
    with open("./bin/log.txt", 'w') as logger:
        try:
            Source("main").compile()
            Object("main").link()

        except Exception as e:
            print(e, end="", file=sys.stderr)
            print(e, end="", file=logger)
            exit(-1)

        except KeyboardInterrupt as e:
            exit(-1)
            
        except:
            raise