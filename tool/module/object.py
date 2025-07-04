from module.compiler import *
from module.module   import *
from module.source   import *

class Object:
    pool    = {}
    current = 0
    total   = 0
    
    def __new__(self, name):
        if name in Object.pool.keys():
            return Object.pool[name]
        else:
            self = super().__new__(self)
            Object.pool[name] = self

            # Info
            self.name            = name
            self.object_file     = f"./bin/{type}/module/{self.name}.{object_suffix}"
            self.library_file    = f"./bin/{type}/module/{self.name}.{library_suffix}" if os.path.isfile(f"./bin/{type}/module/{self.name}.{library_suffix}") else None
            self.executable_file = f"./bin/{type}/{self.name}.{executable_suffix}"     if executable_suffix != "" else f"./bin/{type}/{self.name}"
                
            # Import
            if self.name in Source.pool.keys():
                self.import_objects = [Object(import_module.name) for import_module in Source(name=self.name).import_modules]
            else:
                self.import_objects = [Object(import_module.name) for import_module in Module(name=self.name).import_modules]

            # Built
            self.is_built = os.path.isfile(self.executable_file) and os.path.getmtime(self.object_file) <= os.path.getmtime(self.executable_file)
            if not self.is_built:
                Object.total += 1

            # Return
            return self

    def link(self):
        if not self.is_built:
            Object.current += 1
            print(f"link object [{Object.current}/{1}]: {self.name}")
            link_object(object_files=self._recursive_linkable_files(), executable_file=self.executable_file)

    def _recursive_linkable_files(self, linkable_files=[]):
        if not self.object_file in linkable_files:
            linkable_files += [self.object_file]
        if self.library_file is not None and not self.library_file in linkable_files:
            linkable_files += [self.library_file]
        for import_object in self.import_objects:
            import_object._recursive_linkable_files(linkable_files)
        return linkable_files