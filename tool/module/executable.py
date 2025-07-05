from module.compiler import *
from module.module   import *
from module.source   import *
from module.object   import *

class Executable:
    pool    = {}
    current = 0
    total   = 0
    
    def __new__(self, name):
        if name in Executable.pool.keys():
            return Executable.pool[name]
        else:
            self = super().__new__(self)
            Executable.pool[name] = self

            # Info
            self.name            = name
            self.executable_file = f"./bin/{type}/{self.name.replace('.', '/', 1)}.{executable_suffix}" if executable_suffix != "" else f"./bin/{type}/{self.name.replace('.', '/', 1)}"
            
            # Built
            Executable.total += 1

            # Return
            return self

    def run(self):
        Executable.current += 1
        print(f"run executable [{Executable.current}/{Executable.total}]: {self.name}")
        run(f"./{self.executable_file}")