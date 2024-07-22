import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

data = [
    {"Operation": "Q1", "Coarse": 2, "Medium": 2, "DomLock": 819, "MID": 3460, "FlexiGran": 1468, "CALock": 10, "Intention Lock": 2},
    {"Operation": "Q2", "Coarse": 2, "Medium": 2, "DomLock": 2287, "MID": 3564, "FlexiGran": 13086, "CALock": 34, "Intention Lock": 12},
    {"Operation": "OP1", "Coarse": 2, "Medium": 2, "DomLock": 1557, "MID": 1652, "FlexiGran": 1604, "CALock": 18, "Intention Lock": 2},
    {"Operation": "OP2", "Coarse": 2, "Medium": 2, "DomLock": 809, "MID": 1652, "FlexiGran": 1652, "CALock": 11, "Intention Lock": 4},
    {"Operation": "OP3", "Coarse": 34, "Medium": 5, "DomLock": 1557, "MID": 3460, "FlexiGran": 2985, "CALock": 10, "Intention Lock": 3},
    {"Operation": "OP4", "Coarse": 31, "Medium": 6, "DomLock": 1557, "MID": 5082, "FlexiGran": 14300, "CALock": 36, "Intention Lock": 14},
    {"Operation": "SM1", "Coarse": 23, "Medium": 193, "DomLock": 791, "MID": 1652, "FlexiGran": 1604, "CALock": 20, "Intention Lock": 2},
    {"Operation": "SM2", "Coarse": 25, "Medium": 248, "DomLock": 1557, "MID": 3460, "FlexiGran": 1702, "CALock": 19, "Intention Lock": 2},
]
custom_colors = {
    'Coarse': '#58b5e1',
    'Medium': '#b7d165',
    'Intention Lock': '#ab2b60',
    'DomLock': '#56ebd3',
    'MID': '#965a5b',
    'FlexiGran': '#d8a06c',
    'CALock': '#335862',
}

order = {"Coarse": 0, "Medium": 1, "Intention Lock": 2, "DomLock": 3, "MID": 4, "FlexiGran": 5, "CALock": 6}
df = pd.DataFrame(data)
df_melted = pd.melt(df, id_vars=['Operation'], value_vars=['Coarse', 'Medium','Intention Lock', 'DomLock', 'MID', 'FlexiGran', 'CALock'],
                    var_name='Lock Type', value_name='Time')
final = df_melted.sort_values(by=["Lock Type"], key=lambda x: x.map(order))
palette = [custom_colors[lock] for lock in final['Lock Type'].unique()]

lockRejections = [{
    "Q1": 458,
    "Q2": 299,
    "OP1": 625,
    "OP2": 614,
    "OP3": 10017,
    "OP4": 5503,
    "SM1": 247,
    "SM2": 261
}]

lockRejections = pd.DataFrame(lockRejections)
lockRejections = lockRejections.melt(var_name='Operation', value_name='Rejections')


sns.set_theme(style='whitegrid', palette=palette)
g = sns.catplot(x='Operation', y='Time', hue='Lock Type', data=final, kind='bar', height=3, aspect=2)
g1= sns.pointplot(data=lockRejections, x='Operation', y='Rejections', color='grey', markers="." ,linestyles='--', ax=g.ax, legend=False)
for(_, value) in lockRejections.iterrows():
    plt.annotate(value['Rejections'], (value['Operation'], value['Rejections']), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)
g.despine(left=True)
g.set_axis_labels("Operation", "Time to Completion ($\mu$s logscale)")
g.legend.set_title("")
g.set(yscale="log")
sns.move_legend(g, loc='upper center', ncols=4, fancybox=True,  bbox_to_anchor=(0.46, 1.1))

plt.savefig("./benchmarkCharts/TTC.png", dpi=300, bbox_inches="tight")
