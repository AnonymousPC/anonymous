from module.source     import *
from module.object     import *
from module.executable import *
from module.init       import *

if __name__ == "__main__":
    try:
        units = []
        for root, _, files in os.walk("./test"):
            for file in files:
                if file.endswith(".cpp"):
                    unit = f"{root.replace('/', '.').lstrip('.')}.{file.removesuffix(".cpp")}"
                    Source    (unit)
                    Object    (unit)
                    Executable(unit)
                    units += [unit]

        for unit in units:
            Source(unit).compile()
        for unit in units:
            Object(unit).link()
        for unit in units:
            Executable(unit).run()
                
    except Exception as e:
        print(e, end="", file=sys.stderr)
        print(e, end="", file=open(".log", 'a'))
        exit(-1)

    except KeyboardInterrupt as e:
        exit(-1)
        
    except:
        raise
