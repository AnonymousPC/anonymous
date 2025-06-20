from compiler import *
from config import *

class Binary:
    def __init__(self, executable):
        self.executable = executable

    def link(self):
        print(f"link binary [1/1]: {self.executable}")
        link(executable_path=f"./bin/{self.executable}{executable_suffix}")