import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

data = [
    {"Operation": "Q1", "Coarse": 2, "Medium": 2, "DomLock": 819, "MID": 3460, "FlexiGran": 1468, "CALock": 10},
    {"Operation": "Q2", "Coarse": 2, "Medium": 2, "DomLock": 2287, "MID": 3564, "FlexiGran": 13086, "CALock": 34},
    {"Operation": "OP1", "Coarse": 2, "Medium": 2, "DomLock": 1557, "MID": 1652, "FlexiGran": 1604, "CALock": 18},
    {"Operation": "OP2", "Coarse": 2, "Medium": 2, "DomLock": 809, "MID": 1652, "FlexiGran": 1652, "CALock": 11},
    {"Operation": "OP3", "Coarse": 34, "Medium": 5, "DomLock": 1557, "MID": 3460, "FlexiGran": 2985, "CALock": 10},
    {"Operation": "OP4", "Coarse": 31, "Medium": 6, "DomLock": 1557, "MID": 5082, "FlexiGran": 14300, "CALock": 36},
    {"Operation": "SM1", "Coarse": 23, "Medium": 193, "DomLock": 791, "MID": 1652, "FlexiGran": 1604, "CALock": 2},
    {"Operation": "SM2", "Coarse": 25, "Medium": 248, "DomLock": 1557, "MID": 3460, "FlexiGran": 1702, "CALock": 19},
]

order = {"Coarse": 0, "Medium": 1, "DomLock": 2, "MID": 3, "FlexiGran": 4, "CALock": 5}
df = pd.DataFrame(data)
df_melted = pd.melt(df, id_vars=['Operation'], value_vars=['Coarse', 'Medium', 'DomLock', 'MID', 'FlexiGran', 'CALock'],
                    var_name='Lock Type', value_name='Time')
final = df_melted.sort_values(by=["Lock Type"], key=lambda x: x.map(order))

sns.set_theme(style='whitegrid')
g = sns.catplot(x='Operation', y='Time', hue='Lock Type', data=final, kind='bar', height=3, aspect=2, palette="viridis")
g.despine(left=True)
g.set_axis_labels("Operation", "Time to Completion ($\mu$s logscale)")
g.legend.set_title("")
g.set(yscale="log")
sns.move_legend(g, loc='upper center', ncols=3, fancybox=True,  bbox_to_anchor=(0.45, 1.1))

plt.savefig("./benchmarkCharts/TTC.png", dpi=300, bbox_inches="tight")
