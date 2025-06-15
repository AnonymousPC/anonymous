from compiler import *
from config import *
from progress_bar import *

class Binary:
    def __init__(self, executable):
        self.executable = executable

    def link(self):
        with progress_bar.prefix(f"link binary [1/1]: {self.executable}"):
            link(executable_path=f"./bin/{self.executable}{executable_suffix}")