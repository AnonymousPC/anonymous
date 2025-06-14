import sys
sys.dont_write_bytecode = True
import argparse
import os
from attribute import *
from binary import *
from compiler import *
from config import *
from module import *

# Environment
if __name__ == "__main__":
    os.chdir(f"{os.path.dirname(__file__)}/../..")
    sys.dont_write_bytecode = True

    try:
        parser = argparse.ArgumentParser(description="build.py")
        parser.add_argument("--type",  choices=["debug", "release"], default="debug")
        parser.add_argument("--clean", action="store_true")

        try:
            args = parser.parse_args()
        except argparse.ArgumentException:
            raise Exception("Usage: [--type {debug,release}] [--clean]")
        

        if not args.clean:
            type = args.type
            Module("main").compile()
            Binary("main").link()

        else:
            for file in os.listdir(f"./bin/{type}/module"):
                os.remove         (f"./bin/{type}/module/{file}")
            for dir  in os.listdir(f"./bin/{type}/cmake"):
                shutil.rmtree     (f"./bin/{type}/cmake/{dir}")

    except Exception as e:
        print(e, file=sys.stderr)
        print(e, file=open(f"./bin/log.txt", 'w'))
        exit(-1)

    except KeyboardInterrupt as e:
        exit(-1)
