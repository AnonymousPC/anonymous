from module.compiler import *

class Object:
    current = 0
    total   = 0
    
    def __init__(self, object_name):
        # Info
        self.object_name     = object_name
        self.object_file     = f"./bin/{type}/module/{self.object_name}.{object_suffix}"
        self.executable_file = f"./bin/{self.object_name}.{executable_suffix}" if executable_suffix != "" else f"./bin/{self.object_name}"

        # Built
        self.is_built = os.path.isfile(self.executable_file) and os.path.getmtime(self.object_file) <= os.path.getmtime(self.executable_file)
        if not self.is_built:
            Object.total += 1

    def link(self):
        if not self.is_built:
            Object.current += 1
            print(f"link object [{Object.current}/{Object.total}]: {self.object_name}")
            link_binary(object_dir=os.path.dirname(self.object_file), lib_dir=f"./bin/{type}/third_party/install/lib", executable_file=self.executable_file)