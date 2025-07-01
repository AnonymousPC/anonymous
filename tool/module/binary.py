from module.compiler import *
from module.config import *

class Binary:
    def __init__(self, executable):
        self.executable = executable

    def link(self):
        print(f"link binary [1/1]: {self.executable}")
        if executable_suffix != "":
            link_binary(object_dir=f"./bin/{type}/module", lib_dir=f"./bin/{type}/third_party/install/lib", executable_file=f"./bin/{self.executable}.{executable_suffix}")
        else:
            link_binary(object_dir=f"./bin/{type}/module", lib_dir=f"./bin/{type}/third_party/install/lib", executable_file=f"./bin/{self.executable}")