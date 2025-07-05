from module.compiler import *
from module.module   import *
  
class Source:
    pool    = {}
    current = 0
    total   = 0

    def __new__(self, name):
        if name in Source.pool.keys():
            return Source.pool[name]
        else:
            self = super().__new__(self)
            Source.pool[name] = self

            # Info
            self.name        = name
            self.code_file   = f"./{self.name.replace('.', '/')}.cpp"
            self.object_file = f"./bin/{type}/module/{self.name}.{object_suffix}"
            self.content     = preprocess_file(code_file=self.code_file)

            # Import
            self.import_modules = []
            import_names = re.findall(r'^\s*(?:export\s+)?import\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
            for import_name in import_names:
                self.import_modules.append(Module(name=import_name))

            # Built
            self.is_compiled = all(module.is_compiled for module in self.import_modules) and os.path.isfile(self.object_file) and os.path.getmtime(self.code_file) <= os.path.getmtime(self.object_file)
            if not self.is_compiled:
                Source.total += 1

            # Return
            return self

    def compile(self):
        # Dependency
        for import_module in self.import_modules:
            if not import_module.is_compiled:
                import_module.compile()

        # Self
        if not self.is_compiled:
            Source.current += 1
            print(f"compile source [{Source.current}/{Source.total}]: {self.name}")
            compile_source(code_file=self.code_file, include_dir=f"./bin/{type}/package/install/include", object_file=self.object_file)
            self.is_compiled = True
    
    def __eq__(self, str: str):
        return self.name == str

