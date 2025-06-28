import subprocess
import threading
from .config import *

def run(command, **kwargs):
    if not verbose:
        try:
            p = subprocess.run(command, shell=True, capture_output=True, check=True, text=True, **kwargs)
            print(p.stderr, end="", file=sys.stderr)
        except subprocess.CalledProcessError as e:
            raise Exception(e.stderr)

    else:
        print(command)
        p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, **kwargs)
        e = ""

        def read_stdout():
            while p.poll() is None:
                print(p.stdout.readline(), end="", file=sys.stdout)
        def read_stderr():
            while p.poll() is None:
                print(p.stderr.readline(), end="", file=sys.stderr)
                nonlocal e
                e += p.stderr.readline()
                
        stdout_thread = threading.Thread(target=read_stdout)
        stderr_thread = threading.Thread(target=read_stderr)
        stdout_thread.start()
        stderr_thread.start()
        stdout_thread.join()
        stderr_thread.join()

        if p.poll() != 0:
            raise Exception(e)