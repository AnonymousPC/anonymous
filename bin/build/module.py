from attribute import *
from compiler import *
from config import *
from progress_bar import *

class Module:
    modules = []
    current = 1
    total = 0

    def __init__(self, export_name, from_modules=[]):
        try:
            self.export_name  = export_name
            self.source_path  = f"./include/{self.export_name.replace('.', '/')}.cpp"
            self.module_path  = f"./bin/{type}/module/{self.export_name}{module_suffix}"
            self.object_path  = f"./bin/{type}/module/{self.export_name}{object_suffix}"
            self.from_modules = from_modules
            self.content      = preprocess(self.source_path)
            Module.modules.append(self)

            self.import_modules = []
            import_strs = re.findall(r'\bimport\s+([\w\.:]+)(?:\s*\[\[.*?\]\])*\s*;', self.content, flags=re.DOTALL)
            for import_str in import_strs:
                if import_str in self.from_modules:
                    raise Exception(f"fatal error: dependency circle detected when trying to import module {import_str}")
                if import_str in Module.modules:
                    self.import_modules.append(Module.modules[Module.modules.index(import_str)])
                else:
                    self.import_modules.append(Module(import_str, from_modules=self.from_modules + [self]))

            self.is_built = all(module.is_built for module in self.import_modules) and \
                            os.path.isfile  (self.module_path) and \
                            os.path.getmtime(self.source_path) <= os.path.getmtime(self.module_path)
            if not self.is_built:
                Module.total += 1

            export_name_strs = re.findall(r'\bexport\s+module\s+([\w\.:]+)(?:\s*\[\[.*?\]\])*\s*;', self.content, flags=re.DOTALL)
            if len(export_name_strs) != 1 or export_name_strs[0] != export_name:
                raise Exception(f"fatal error: file {self.source_path} should export_name module {self.export_name}")

        except Exception as e:
            raise Exception(f"In module imported from {self.export_name}:\n{e}")

    def compile(self):
        try:
            for import_module in self.import_modules:
                if not import_module.is_built:
                    import_module.compile()
            if not self.is_built:
                with progress_bar.prefix(f"compile module [{Module.current}/{Module.total}]: {self.export_name}"):
                    apply_attribute(module=self)
                    compile(source_path=self.source_path, module_path=self.module_path, object_path=self.object_path)
                    self.is_built = True
                    Module.current += 1
        except Exception as e:
            raise Exception(f"In module imported from {self.export_name}:\n{e}")
        
    def __eq__(self, str: str):
        return self.export_name == str

