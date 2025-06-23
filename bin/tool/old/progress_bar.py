import os

class ProgressBar:
    def prefix(self, prefix_str):
        self.prefix_str = prefix_str
        return self

    def suffix(self, suffix_str):
        _print_progress(f"{self.prefix_str} {suffix_str}")

    def __enter__(self):
        _print_progress(self.prefix_str)

    def __exit__(self, *args):
        _print_progress(self.prefix_str)
        print()



def _print_progress(str):
    print(f"\r{str}".replace('\t', ' ').ljust(os.get_terminal_size().columns+1)[:os.get_terminal_size().columns+1], end="")



progress_bar = ProgressBar()
        