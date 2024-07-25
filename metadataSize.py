# Import the necessary modules
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
import sys

# Initialize the lists for X and Y

custom_colors = {
    'Coarse': '#58b5e1',
    'Medium': '#b7d165',
    'Intention Lock': '#ab2b60',
    'DomLock': '#56ebd3',
    'MID': '#965a5b',
    'FlexiGran': '#d8a06c',
    'CALock': '#335862',
}



data = {
    'Type': ['Small', 'Medium', 'Large'],
    'DomLock': [19.088, 33.264, 33.200],
    'MID': [28.632, 49.896, 49.800],
    'FlexiGran': [23.860, 41.620, 41.620],
    'CALock': [58.064, 89.804, 89.700],
}


df = pd.DataFrame(data)
order = {'Coarse': 0, 'Medium': 1, 'Intention Lock': 2, 'DomLock': 3, 'MID': 4, 'FlexiGran': 5, 'CALock': 6}
df_melted = pd.melt(df, id_vars=['Type'], var_name='lock', value_name='value')
# print(df_melted)
final = df_melted.sort_values(by=["lock"], key=lambda x: x.map(order))
palette = [custom_colors[lock] for lock in final['lock'].unique()]

sns.set_theme(style="whitegrid")
g = sns.catplot(data=final, kind="bar", x="Type", y="value", hue="lock", height=3, aspect=2, palette=palette)
g.despine(left=True)
g.set_axis_labels("Hierarchy Size", "Metadata size (Kb)")
g.set_xticklabels(['$Small$', '$Medium$', '$Large$'])
g.legend.set_title("")
sns.move_legend(g,loc='upper center', ncols=4, fancybox=True, bbox_to_anchor=(0.4, 1.1))
plt.savefig("./benchmarkCharts/LabelsMemorySize.png", dpi=300, bbox_inches='tight')


#
#
#
# plt.figure(figsize=(7, 4))
# plt.bar(r1, DomLock, color='#7768AE', width=width, label='Domlock', edgecolor='black')
# plt.bar(r2, MID, color='#4D9DE0', width=width, label='MID', edgecolor='black')
# plt.bar(r3, Flexi, color='#F9BA8F', width=width, label='Flexigran 50%', edgecolor='black')
# plt.bar(r4, CALock, color='#3bb273', width=width, label='CALock', edgecolor='black')
#
# plt.xlabel('Hierarchy Size')
# plt.ylabel('Metadata size (bytes)')
# plt.xticks(r2, ['Small', 'Medium', 'Large'])
# # # Create legend & Show graphic
# plt.grid(axis='y', linestyle='--', linewidth=0.5)
#
# plt.legend(loc='upper center', ncols=3, bbox_to_anchor=(0.5, 1.175), fancybox=True)
# plt.savefig("./benchmarkCharts/LabelsMemorySize.png", dpi=150, bbox_inches="tight")
