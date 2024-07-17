# Import the necessary modules
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
import sys

# Initialize the lists for X and Y

data = {
    'Type': ['Small', 'Medium', 'Large'],
    'CALock': [58064, 89804, 89700],
    'Domlock': [19088, 33264, 33200],
    'MID': [28632, 49896, 49800],
    'Flexi': [23860, 41620, 41620]
}


df = pd.DataFrame(data)
order = {"Domlock": 0, "MID": 1, "Flexi": 2, "CALock": 3}
df_melted = pd.melt(df, id_vars=['Type'], var_name='lock', value_name='value')
# print(df_melted)
final = df_melted.sort_values(by=["lock"], key=lambda x: x.map(order))


sns.set_theme(style="whitegrid")
g = sns.catplot(data=final, kind="bar", x="Type", y="value", hue="lock", height=3, aspect=2, palette="viridis")
g.despine(left=True)
g.set_axis_labels("Hierarchy Size", "Metadata size (bytes)")
g.set_xticklabels(['Small', 'Medium', 'Large'])
g.legend.set_title("")
sns.move_legend(g,loc='upper center', ncols=4, fancybox=True)
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
