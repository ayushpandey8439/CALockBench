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


containment = df.groupby('Type', as_index=False).agg('mean')
# print(containment)

order = {"Domlock": 0, "MID": 1, "Flexi": 2, "CALock": 3}
df_melted = pd.melt(containment, id_vars=['Type'], var_name='lock', value_name='value')
final = df_melted.sort_values(by=["lock"], key=lambda x: x.map(order))
# print(final)

sns.set_theme(style="whitegrid")
g = sns.catplot(data=final, kind="bar", x="Type", y="value", hue="lock", height=3, aspect=2, palette="viridis")
g.despine(left=True)
g.set_axis_labels("Vertex Type", "Vertices locked (log scale)")
g.set_xticklabels(['Complex\nAssembly', 'Base\nAssembly', 'Composite\nPart', 'Atomic\nPart'])
g.legend.set_title("")
sns.move_legend(g,loc='upper center', ncols=4, fancybox=True)
g.set(yscale="log")
plt.savefig("./benchmarkCharts/ContainmentRatio.png", dpi=300, bbox_inches='tight')
