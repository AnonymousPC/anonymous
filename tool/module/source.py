from module.compiler import *
from module.module   import *
  
class Source:
    current = 0
    total   = 0

    def __init__(self, source_name):
        # Info
        self.source_name = source_name
        self.code_file   = f"./{self.source_name}.cpp"
        self.object_file = f"./bin/{type}/module/{self.source_name}.{object_suffix}"
        self.content     = preprocess_file(code_file=self.code_file)

        # Import
        self.import_modules = []
        import_strs = re.findall(r'^\s*(?:export\s+)?import\s+([\w\.:]+)\s*;\s*$', self.content, flags=re.MULTILINE)
        for import_str in import_strs:
            if import_str in Module.modules:
                self.import_modules.append(Module.modules[Module.modules.index(import_str)])
            else:
                self.import_modules.append(Module(import_str, [self]))

        # Built
        self.is_built = all(module.is_built for module in self.import_modules) and os.path.isfile(self.object_file) and os.path.getmtime(self.code_file) <= os.path.getmtime(self.object_file)
        if not self.is_built:
            Source.total += 1

    def compile(self):
        # Dependency
        for import_module in self.import_modules:
            if not import_module.is_built:
                import_module.compile()

        # Self
        if not self.is_built:
            Source.current += 1
            print(f"compile source [{Source.current}/{Source.total}]: {self.source_name}")
            compile_source(code_file=self.code_file, include_dir=f"./bin/{type}/third_party/install/include", object_file=self.object_file)
            self.is_built = True
    
    def __eq__(self, str: str):
        return self.source_name == str

