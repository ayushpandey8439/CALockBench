# Import the necessary modules
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y
data = pd.read_csv("./benchmarkResults/containment.csv")

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column

custom_colors = {
    'Coarse': '#58b5e1',
    'Medium': '#b7d165',
    'Intention Lock': '#ab2b60',
    'DomLock': '#56ebd3',
    'MID': '#965a5b',
    'FlexiGran': '#d8a06c',
    'CALock': '#335862',
}

containment = df.groupby('Type', as_index=False).agg('mean')
# print(containment)

order = {"DomLock": 0, "MID": 1, "FlexiGran": 2, "CALock": 3}

df_melted = pd.melt(containment, id_vars=['Type'], var_name='lock', value_name='value')
final = df_melted.sort_values(by=["lock"], key=lambda x: x.map(order))
# print(final)

x = np.arange(len(containment['Type']))
width = 0.2

plt.figure(figsize=(5, 1.5))
plt.bar(x - 3 * width / 2, containment['DomLock'], color=custom_colors['DomLock'], width=width, label='Domlock')
plt.bar(x - width / 2, containment['MID'], width=width, label='MID', color=custom_colors['MID'])
plt.bar(x + width / 2, containment['FlexiGran'], width=width, label='Flexigran', color=custom_colors['FlexiGran'])
plt.bar(x + 3 * width / 2, containment['CALock'], width=width, label='CALock', color=custom_colors['CALock'])
plt.yscale('log')

plt.xlabel('Vertex Type')
plt.ylabel('Vertices locked (log scale)')
plt.xticks(x, ['$Complex Assm$', '$Base Assm$', '$Composite Part$', '$Atomic Part$'])

plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.3), fancybox=True, ncols=4)
# # Create legend & Show graphic
plt.grid(axis='y', linestyle='--', linewidth=0.5)
plt.savefig("./benchmarkCharts/ContainmentRatio.png", dpi=150, bbox_inches="tight")



#
# palette = [custom_colors[lock] for lock in final['lock'].unique()]
#
# sns.set_theme(style="whitegrid")
# g = sns.catplot(data=final, kind="bar", x="Type", y="value", hue="lock", height=3, aspect=2, palette=palette)
# g.despine(left=True)
# g.set_axis_labels("Vertex Type", "Vertices locked (log scale)")
# g.set_xticklabels(['$Complex~Assm.$', '$Base~Assm.$', '$Composite~Part$', '$Atomic~Part$'])
# g.legend.set_title("")
# sns.move_legend(g,loc='upper center', ncols=4, fancybox=True, bbox_to_anchor=(0.45, 1.1))
# g.set(yscale="log")
# plt.savefig("./benchmarkCharts/ContainmentRatio.png", dpi=300, bbox_inches='tight')
