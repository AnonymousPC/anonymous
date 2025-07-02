from module.compiler import *

class Module:
    modules = []
    current = 0
    total   = 0

    def __init__(self, module_name, from_modules=[]):
        try:
            # Info
            self.module_name  = module_name
            self.code_file    = f"./module/{self.module_name.replace('.', '/')}.cpp"
            self.module_file  = f"./bin/{type}/module/{self.module_name}.{module_suffix}"
            self.object_file  = f"./bin/{type}/module/{self.module_name}.{object_suffix}"
            self.tool_file    = f"./tool/third_party/{self.module_name.partition('.')[0]}.py" if os.path.isfile(f"./tool/third_party/{self.module_name.partition('.')[0]}.py") else None
            self.from_modules = from_modules
            self.content      = preprocess_file(code_file=self.code_file, module_name=self.module_name, module_file=self.module_file)
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
            self.is_built = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_file) and os.path.getmtime(self.code_file) <= os.path.getmtime(self.module_file)
            if not self.is_built:
                Module.total += 1

            # Check
            if self.module_file is not None:
                export_strs = re.findall(r'^\s*export\s+module\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
                if (len(export_strs) != 1 or export_strs[0] != module_name):
                    raise Exception(f"fatal error: file {self.code_file} should export module {self.module_name}")

        except Exception as e:
            raise Exception(f"In module imported from {self.module_name}:\n{e}")

    def compile(self):
        # Dependency
        for import_module in self.import_modules:
            if not import_module.is_built:
                import_module.compile()

        # Self
        if not self.is_built:
            Module.current += 1
            print(f"compile module [{Module.current}/{Module.total}]: {self.module_name}")
            if self.tool_file is not None:
                compile_tool(tool_file=self.tool_file)
            compile_module(code_file=self.code_file, include_dir=f"./bin/{type}/third_party/install/include", module_file=self.module_file, object_file=self.object_file)
            self.is_built = True
        
    def __eq__(self, str: str):
        return self.module_name == str

