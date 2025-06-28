from .compiler import *
from .config import *

class Binary:
    def __init__(self, executable):
        self.executable = executable

    def link(self):
        print(f"link binary [1/1]: {self.executable}")
        if executable_suffix != "":
            link_binary(object_dirs=[f"./bin/{type}", "./third_party/lib"], executable_path=f"./bin/{self.executable}.{executable_suffix}")
        else:
            link_binary(object_dirs=[f"./bin/{type}", "./third_party/lib"], executable_path=f"./bin/{self.executable}")