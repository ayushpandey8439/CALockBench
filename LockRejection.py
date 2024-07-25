import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

data = [
    {
        '1': 0,
        '2': 15,
        '4': 31,
        '8': 64,
        '16': 127,
        '32': 262,
        '64': 419,
    }
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

df = pd.DataFrame(data)
sns.set_theme(style='whitegrid')
df_melted = pd.melt(df, var_name='Thread Count', value_name='Rejection')

g = sns.catplot(x='Thread Count', y='Rejection', data=df_melted, kind='point', height=3, aspect=4, legend=False, color='grey')
# g1= sns.pointplot(data=lockRejections, x='Operation', y='Rejections', color='grey', markers="." ,linestyles='--', ax=g.ax, legend=False)
# for(_, value) in lockRejections.iterrows():
#     plt.annotate(value['Rejections'], (value['Operation'], value['Rejections']), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)
g.despine(left=True)
g.set_axis_labels("Thread Count", "Locks rejected")
# g.legend.set_title("")
# g.set(yscale="log")
# sns.move_legend(g, loc='upper center', fancybox=True,  bbox_to_anchor=(0.46, 1.1))

plt.savefig("./benchmarkCharts/LockRejection.png", dpi=300, bbox_inches="tight")
