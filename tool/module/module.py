from module.compiler import *

class Module:
    pool    = {}
    current = 0
    total   = 0

    def __new__(self, name, from_modules=[]):
        if name in Module.pool.keys():
            return Module.pool[name]
        else:
            self = super().__new__(self)
            Module.pool[name] = self

            try:
                # Info
                self.name         = name
                self.code_file    = f"./module/{self.name.replace('.', '/')}.cpp"
                self.module_file  = f"./bin/{type}/module/{self.name}.{module_suffix}"
                self.object_file  = f"./bin/{type}/module/{self.name}.{object_suffix}"
                self.library_file = f"./bin/{type}/module/{self.name}.{library_suffix}" if os.path.isfile(f"./bin/{type}/module/{self.name}.{library_suffix}") else None
                self.tool_file    = f"./tool/package/{self.name.partition('.')[0]}.py"  if os.path.isfile(f"./tool/package/{self.name.partition('.')[0]}.py")  else None
                self.from_modules = from_modules
                self.content      = preprocess_file(code_file=self.code_file, name=self.name, module_file=self.module_file)

                # Import
                self.import_modules = []
                import_names = re.findall(r'^\s*(?:export\s+)?import\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
                for import_name in import_names:
                    if import_name in self.from_modules:
                        raise Exception(f"fatal error: dependency circle detected when trying to import module {import_name}")
                    self.import_modules.append(Module(name=import_name, from_modules=self.from_modules + [self]))

                # Built
                self.is_built = all(module.is_built for module in self.import_modules) and os.path.isfile(self.module_file) and os.path.getmtime(self.code_file) <= os.path.getmtime(self.module_file)
                if not self.is_built:
                    Module.total += 1

                # Check
                if self.module_file is not None:
                    export_names = re.findall(r'^\s*export\s+module\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
                    if (len(export_names) != 1 or export_names[0] != self.name):
                        raise Exception(f"fatal error: file {self.code_file} should export module {self.name}")
                    
                # Return
                return self

            except Exception as e:
                raise Exception(f"In module imported from {self.name}:\n{e}")

    def compile(self):
        # Dependency
        for import_module in self.import_modules:
            if not import_module.is_built:
                import_module.compile()

        # Self
        if not self.is_built:
            Module.current += 1
            print(f"compile module [{Module.current}/{Module.total}]: {self.name}")
            if self.tool_file is not None:
                compile_tool(tool_file=self.tool_file)
            compile_module(code_file=self.code_file, include_dir=f"./bin/{type}/package/install/include", module_file=self.module_file, object_file=self.object_file)
            self.is_built = True
        
    def __eq__(self, str: str):
        return self.name == str

