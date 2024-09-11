# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
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
    'DomLock': [4.39985e+01,4.3434e+01,5.68294e+02],
    'MID': [8.9518e+01, 9.08921e+01, 1.14594e+03],
    'FlexiGran': [4.32685e+01,5.6863e+01,7.06276e+02],
    'CALock': [4.13138e+02, 6.71705e+02,6.50443e+03]
}

df = pd.DataFrame(data)

x = np.arange(len(df['Type']))
width = 0.2

plt.figure(figsize=(5,1.5))
plt.bar(x - 3 * width / 2, df['DomLock'], color= custom_colors['DomLock'] , width=width, label='Domlock')
plt.bar(x - width / 2, df['MID'],  width=width, label='MID', color = custom_colors['MID'])
plt.bar(x + width / 2, df['FlexiGran'], width=width, label='Flexigran', color = custom_colors['FlexiGran'])
plt.bar(x + 3 * width / 2, df['CALock'], width=width, label='CALock', color = custom_colors['CALock'])

plt.yscale('log')
plt.ylabel('Labelling time ($\mu$s log)')
plt.xlabel('Hierarchy Size')
plt.xticks(x, ['$Small$', '$Medium$', '$Large$'])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.3), fancybox=True, ncols=4)
plt.grid(axis='y', linestyle='--', linewidth=0.5)
plt.savefig("./benchmarkCharts/InitialLabelling.png", dpi=150, bbox_inches="tight")


# order = {'Coarse': 0, 'Medium': 1, 'Intention Lock': 2, 'DomLock': 3, 'MID': 4, 'FlexiGran': 5, 'CALock': 6}
# df_melted = pd.melt(df, id_vars=['Type'], var_name='lock', value_name='value')
# # print(df_melted)
# final = df_melted.sort_values(by=['lock'], key=lambda x: x.map(order))
# palette = [custom_colors[lock] for lock in final['lock'].unique()]
#
# sns.set_theme(style="whitegrid",palette=palette)
# g = sns.catplot(data=final, kind="bar", x="Type", y="value", hue="lock", height=3, aspect=2)
# g.despine(left=True)
# g.set_axis_labels("Hierarchy Size", "Labelling time ($\mu$s logscale)")
# g.set_xticklabels(['$Small$', '$Medium$', '$Large$'])
# g.legend.set_title("")
# g.set(yscale="log")
# sns.move_legend(g,loc='upper center', ncols=4, fancybox=True, bbox_to_anchor=(0.4, 1.1))
# plt.savefig("./benchmarkCharts/InitialLabelling.png", dpi=300, bbox_inches="tight")
#
# # plt.show()