from attribute import *
from compiler import *
from config import *
from progress_bar import *

class Module:
    modules = []
    current = 1
    total = 0

    def __init__(self, export, from_modules=[]):        
        try:
            self.export         = export
            self.source_path    = f"./include/{export.replace('.', '/')}.cpp"
            self.module_path    = f"./bin/{type}/module/{export}{module_suffix}"
            self.object_path    = f"./bin/{type}/module/{export}{object_suffix}"
            self.from_modules   = from_modules

            self.content        = preprocess(self.source_path)
            self.import_modules = _parse_import_modules(content=self.content, from_modules=self.from_modules, export=self.export)
            self.is_built       = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_path) and os.path.getmtime(self.source_path) <= os.path.getmtime(self.module_path)

            if not self.is_built:
                Module.total += 1

            _check_export(source_path=self.source_path, content=self.content, export=self.export)

        except Exception as e:
            raise Exception(f"In module imported from {self.export}:\n{e}")

    def compile(self):
        try:
            for import_module in self.import_modules:
                if not import_module.is_built:
                    import_module.compile()
            if not self.is_built:
                with progress_bar.prefix(f"compile module [{Module.current}/{Module.total}]: {self.export}"):
                    apply_attribute(module=self)
                    compile(source_path=self.source_path, module_path=self.module_path, object_path=self.object_path)
                    self.is_built = True
                    Module.current += 1
        except Exception as e:
            raise Exception(f"In module imported from {self.export}:\n{e}")



# detail
        
def _parse_import_modules(content, from_modules, export):
    import_modules = []
    names = re.findall(r'\bimport\s+([\w\.:]+)(?:\s*\[\[.*?\]\])*\s*;', content, flags=re.DOTALL)
    for name in names:
        for module in Module.modules:
            if module.export == name:
                import_modules.append(module)
            
        if not name in from_modules:
            module = Module(name, from_modules + [export])
            Module.modules.append(module)
            import_modules.append(module)
        else:
            raise Exception(f"fatal error: dependency circle detected when trying to import module {name}")
    return import_modules
    
def _check_export(source_path, content, export):
    export_strs = re.findall(r'\bexport\s+module\s+([\w\.:]+)(?:\s*\[\[.*?\]\])*\s*;', content, flags=re.DOTALL)
    if len(export_strs) != 1 or export_strs[0] != export:
        raise Exception(f"fatal error: file {source_path} should export module {export}")