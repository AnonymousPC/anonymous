import matplotlib.pyplot as plt
import networkx as nx
import numpy as np
from module.source import *

G = nx.DiGraph()

def _get_name(module):
    if hasattr(module, "source_name"):
        return module.source_name
    elif hasattr(module, "module_name"):
        return module.module_name

def _summon_graph(module):
    G.add_node(_get_name(module))
    for import_module in module.import_modules:
        G.add_node(_get_name(import_module))
        G.add_edge(_get_name(module), _get_name(import_module))
        _summon_graph(import_module)

_summon_graph(Source("main"))



row    = int(len(G.nodes) ** 0.5 + 1)
column = int(len(G.nodes) ** 0.5 + 1)
points = list(nx.grid_2d_graph(row, column).nodes)[:len(G.nodes)]
pos    = {node: point for node, point in zip(sorted(G.nodes), points)}

nx.draw(G, pos=pos, with_labels=True)
plt.show()