# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import numpy as np
import sys
# Initialize the lists for X and Y


data = {
    'Type': ['Small', 'Medium', 'Large'],
    'CALock': [4.13138e+08, 6.71705e+08,6.50443e+09],
    'Domlock': [4.39985e+07,4.3434e+07,5.68294e+08],
    'MID': [8.9518e+07, 9.08921e+07, 1.14594e+09],
    'Flexi': [4.32685e+07,5.6863e+07,7.06276e+08]
}

df = pd.DataFrame(data)
order = {"Domlock": 0, "MID": 1, "Flexi": 2, "CALock": 3}
df_melted = pd.melt(df, id_vars=['Type'], var_name='lock', value_name='value')
# print(df_melted)
final = df_melted.sort_values(by=["lock"], key=lambda x: x.map(order))


sns.set_theme(style="whitegrid")
g = sns.catplot(data=final, kind="bar", x="Type", y="value", hue="lock", height=3, aspect=2, palette="viridis")
g.despine(left=True)
g.set_axis_labels("Hierarchy Size", "Labelling time (ns logscale)")
g.set_xticklabels(['Small', 'Medium', 'Large'])
g.legend.set_title("")
g.set(yscale="log")
sns.move_legend(g,loc='upper center', ncols=4, fancybox=True)
plt.savefig("./benchmarkCharts/InitialLabelling.png", dpi=150, bbox_inches="tight")

# plt.show()