from .compiler import *

class Module:
    modules = []
    current = 1
    total = 0

    def __init__(self, export_name, from_modules=[]):
        try:
            # Info
            if export_name == "main":
                self.export_name = export_name
                self.source_path = f"./{self.export_name.replace('.', '/')}.cpp"
                self.module_path = None
                self.object_path = f"./bin/{type}/{self.export_name}.{object_suffix}"
            else:
                self.export_name = export_name
                self.source_path = f"./module/{self.export_name.replace('.', '/')}.cpp"
                self.module_path = f"./bin/{type}/{self.export_name}.{module_suffix}"
                self.object_path = f"./bin/{type}/{self.export_name}.{object_suffix}"
            self.from_modules = from_modules
            self.content      = preprocess_file(source_path=self.source_path, module_path=self.module_path)
            Module.modules.append(self)

            # Import
            self.import_modules = []
            import_strs = re.findall(r'^\s*(?:export\s+)?import\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
            for import_str in import_strs:
                if import_str in self.from_modules:
                    raise Exception(f"fatal error: dependency circle detected when trying to import module {import_str}")
                if import_str in Module.modules:
                    self.import_modules.append(Module.modules[Module.modules.index(import_str)])
                else:
                    self.import_modules.append(Module(import_str, from_modules=self.from_modules + [self]))

            # Built
            if self.module_path is not None:
                self.is_built = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_path) and os.path.getmtime(self.source_path) <= os.path.getmtime(self.module_path)
            else:
                self.is_built = False
            if not self.is_built:
                Module.total += 1

            # Check
            if self.module_path is not None:
                export_strs = re.findall(r'^\s*export\s+module\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
                if (len(export_strs) != 1 or export_strs[0] != export_name):
                    raise Exception(f"fatal error: file {self.source_path} should export module {self.export_name}")

        except Exception as e:
            raise Exception(f"In module imported from {self.export_name}:\n{e}")

    def compile(self):
        try:
            # Dependency
            for import_module in self.import_modules:
                if not import_module.is_built:
                    import_module.compile()

            # Self
            if not self.is_built:
                print(f"compile module [{Module.current}/{Module.total}]: {self.export_name}")
                if self.module_path is not None:
                    compile_module(source_path=self.source_path, module_path=self.module_path, object_path=self.object_path)
                else:
                    compile_source(source_path=self.source_path, object_path=self.object_path)
                self.is_built = True
                Module.current += 1

        except Exception as e:
            raise Exception(f"In module imported from {self.export_name}:\n{e}")
        
    def __eq__(self, str: str):
        return self.export_name == str

