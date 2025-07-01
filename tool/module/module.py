from module.compiler import *
from module.make import *

class Module:
    modules = []
    current = 1
    total = 0

    def __init__(self, export_name, from_modules=[]):
        try:
            # Info
            if export_name == "main":
                self.export_name = export_name
                self.source_file = f"./{self.export_name.replace('.', '/')}.cpp"
                self.module_file = None
                self.object_file = f"./bin/{type}/module/{self.export_name}.{object_suffix}"
                self.tool_file   = None
            else:
                self.export_name = export_name
                self.source_file = f"./module/{self.export_name.replace('.', '/')}.cpp"
                self.module_file = f"./bin/{type}/module/{self.export_name}.{module_suffix}"
                self.object_file = f"./bin/{type}/module/{self.export_name}.{object_suffix}"
                self.tool_file   = f"./tool/third_party/{self.export_name}.py" if os.path.isfile(f"./tool/third_party/{self.export_name}.py") else None
            self.from_modules = from_modules
            self.content      = preprocess_file(export_name=self.export_name, source_file=self.source_file, module_file=self.module_file)
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
            if self.module_file is not None:
                self.is_built = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_file) and os.path.getmtime(self.source_file) <= os.path.getmtime(self.module_file)
            else:
                self.is_built = False
            if not self.is_built:
                Module.total += 1

            # Check
            if self.module_file is not None:
                export_strs = re.findall(r'^\s*export\s+module\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
                if (len(export_strs) != 1 or export_strs[0] != export_name):
                    raise Exception(f"fatal error: file {self.source_file} should export module {self.export_name}")

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
                if self.tool_file is not None:
                    compile_tool  (tool_file=self.tool_file)
                if self.module_file is not None:
                    compile_module(source_file=self.source_file, include_dir=f"./bin/{type}/third_party/install/include", module_file=self.module_file, object_file=self.object_file)
                else:
                    compile_source(source_file=self.source_file, include_dir=f"./bin/{type}/third_party/install/include", object_file=self.object_file)
                self.is_built = True
                Module.current += 1

        except Exception as e:
            raise Exception(f"In module imported from {self.export_name}:\n{e}")
        
    def __eq__(self, str: str):
        return self.export_name == str

