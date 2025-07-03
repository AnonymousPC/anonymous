import matplotlib.pyplot as plt
import networkx as nx
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

def _get_rgb(rank, total):
    k = rank / (total - 1)
    if 0.00 <= k <= 0.25:
        r = 1
        g = 4 * (k - 0.0)
        b = 0
    elif 0.25 <= k <= 0.50:
        r = 1 - 4 * (k - 0.25)
        g = 1
        b = 0
    elif 0.50 <= k <= 0.75:
        r = 0
        g = 1
        b = 4 * (k - 0.50)
    elif 0.75 <= k <= 1.00:
        r = 0
        g = 1 - 4 * (k - 0.75)
        b = 1
    return r, g, b

_summon_graph(Source("main"))
node_pos    = nx.spring_layout(G, k=1.6, iterations=100, scale=1.0)
label_pos   = {k: (v[0], v[1] + 0.05) for k, v in node_pos.items()}
ancest_dict = {node: len(nx.ancestors(G, node)) for node in G.nodes}
ancest_seq  = list(reversed(sorted(list(set(ancest_dict.values())))))
rank_dict   = {node: ancest_seq.index(ancest_dict[node]) for node in G.nodes}
node_color  = [_get_rgb(rank=rank_dict[node], total=len(ancest_seq)) for node in G.nodes]
nx.draw                (G, pos=node_pos,  node_size=100, node_shape='.', edge_color="#B0B0B0", width=0.5, with_labels=False, node_color=node_color)
nx.draw_networkx_labels(G, pos=label_pos, font_size=8,   font_weight="bold")
plt.show()
