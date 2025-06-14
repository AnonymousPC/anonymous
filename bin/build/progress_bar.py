import os

class ProgressBar:
    def prefix(self, prefix_str):
        self.prefix_str = prefix_str

    def suffix(self, suffix_str):
        print(f"\r{self.prefix_str} {suffix_str}".replace('\t', ' ').ljust(os.get_terminal_size().columns)[:os.get_terminal_size().columns], end="")

    def __enter__(self):
        print(f"\r{self.prefix_str}"             .replace('\t', ' ').ljust(os.get_terminal_size().columns)[:os.get_terminal_size().columns], end="")
        return self

    def __exit__(self, *args):
        print(f"\r{self.prefix_str}"             .replace('\t', ' ').ljust(os.get_terminal_size().columns)[:os.get_terminal_size().columns], end="")
        print()


progress_bar = ProgressBar()
        