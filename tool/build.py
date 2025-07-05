from module.source import *
from module.object import *
from module.init   import *

if __name__ == "__main__":
    try:
        Source("main").compile()
        Object("main").link()

    except Exception as e:
        print(e, end="", file=sys.stderr)
        print(e, end="", file=open(".log", 'a'))
        exit(-1)

    except KeyboardInterrupt as e:
        exit(-1)
        
    except:
        raise