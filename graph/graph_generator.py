import networkx as nx
import matplotlib.pyplot as plt

# Crear un grafo vacío
G = nx.DiGraph()

# Agregar nodos a la grilla
num_filas = 8
num_columnas = 14

for i in range(num_filas):
    for j in range(num_columnas):
        node_id = i * num_columnas + j
        G.add_node(node_id, pos=(j, -i))  # Usar coordenadas (j, -i) para una orientación más natural

# Agregar aristas entre nodos vecinos
adjacency_lists = {
    0: [  1 ],
    1: [  2,   0,  15],
    2: [  3,   1],
    3: [  4,   2,  17],
    4: [  5,   3],
    5: [  6,   4,  19],
    6: [  7,   5],
    7: [  8,   6,  21],
    8: [  9,   7],
    9: [ 10,   8,  23],
    10: [ 11,   9],
    11: [ 12,  10,  25],
    12: [ 13,  11],
    13: [ 12,  27],
    14: [ 15,   0],
    15: [ 16,  29],
    16: [ 17,   2],
    17: [ 18,  31],
    18: [ 19,   4],
    19: [ 20,  33],
    20: [ 21,   6],
    21: [ 22],
    22: [ 23,   8],
    23: [ 24,  37],
    24: [ 25,  10],
    25: [ 26,  39],
    26: [ 27,  12],
    27: [ 41,  13],
    28: [ 14],
    29: [ 28,  43],
    30: [ 29,  16],
    31: [ 30,  45],
    32: [ 31,  18],
    33: [ 32,  47],
    34: [ 33,  20],
    35: [ 34],
    36: [ 35,  22],
    37: [ 36,  51],
    38: [ 37,  24],
    39: [ 38,  53],
    40: [ 39,  26],
    41: [ 40,  55,  27],
    42: [ 43,  28],
    43: [ 44,  57],
    44: [ 45,  30],
    45: [ 46,  59],
    46: [ 47,  32],
    47: [ 48,  61],
    48: [ 49,  34],
    49: [ 63],
    50: [ 36],
    51: [ 52,  65],
    52: [ 53,  38],
    53: [ 54,  67],
    54: [ 55,  40],
    55: [ 69,  41],
    56: [ 42],
    57: [ 56,  71],
    58: [ 57,  44],
    59: [ 58,  73],
    60: [ 59,  46],
    61: [ 60,  75],
    62: [ 61,  48],
    63: [ 62,  77],
    64: [ 63,  50],
    65: [ 64,  79],
    66: [ 65,  52],
    67: [ 66,  81],
    68: [ 67,  54],
    69: [ 68,  83,  55],
    70: [ 71,  56],
    71: [ 72,  85],
    72: [ 73,  58],
    73: [ 74,  87],
    74: [ 75,  60],
    75: [ 76,  89],
    76: [ 77,  62],
    77: [ 78,  91],
    78: [ 79,  64],
    79: [ 80,  93],
    80: [ 81,  66],
    81: [ 82,  95,  66, 96],
    82: [ 83,  68],
    83: [ 97,  69],
    84: [ 70],
    85: [ 84,  99],
    86: [ 85,  72],
    87: [ 86, 101],
    88: [ 87,  74],
    89: [ 88, 103],
    90: [ 89,  76],
    91: [ 90, 105],
    92: [ 91,  78],
    93: [ 92, 107],
    94: [ 93,  80],
    95: [ 94, 109],
    96: [ 95,  82,  81, 111, 97],
    97: [ 111,  83],
    98: [ 99,  84],
    99: [100,  98],
    100: [101,  99,  86],
    101: [102, 100],
    102: [103, 101,  88],
    103: [104, 102],
    104: [105, 103,  90],
    105: [106, 104],
    106: [107, 105,  92],
    107: [108, 106],
    108: [109, 107,  94],
    109: [110, 108],
    110: [111, 109,  96],
    111: [110,  97,  96],

}
for vertex, neighbors in adjacency_lists.items():
    G.add_node(vertex)
    G.add_edges_from((vertex, neighbor) for neighbor in neighbors)

# Visualizar el grafo
pos = nx.get_node_attributes(G, 'pos')
nx.draw(G, pos, with_labels=True, font_weight='bold', node_size=700, node_color='skyblue')

labels = {node: f'({-1*pos[node][1]}, {pos[node][0]})' for node in G.nodes()}
label_pos = {node: (pos[node][0] + 0.3, pos[node][1] - 0.05) for node in G.nodes}
nx.draw_networkx_labels(G, label_pos, labels, font_size=8, font_color='black', verticalalignment='top')

plt.show()