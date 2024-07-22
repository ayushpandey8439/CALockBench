# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
import sys

from pandas import concat

# print(sys.argv[1], sys.argv[2], sys.argv[3])
ThreadCount = int(sys.argv[1])
Iterations = int(sys.argv[2])
WorkloadType = sys.argv[3]
custom_colors = {
    'Coarse': '#58b5e1',
    'Medium': '#b7d165',
    'Intention Lock': '#ab2b60',
    'DomLock': '#56ebd3',
    'MID': '#965a5b',
    'FlexiGran': '#d8a06c',
    'CALock': '#335862',
}

emptyDF = {'ThreadCount': [], 'Coarse': [], 'Medium': [], 'DomLock': [], 'CALock': [], 'MID': [], 'FlexiGran': [],
           'Intention Lock': []}

throughput = pd.DataFrame(emptyDF)
idleness = pd.DataFrame(emptyDF)
relabelling = pd.DataFrame(emptyDF)
# read ThreadCount files
i = 1
while i <= ThreadCount:
    coarse = pd.read_csv("./benchmarkResults/coarse" + str(i) + ".csv", header=None, delimiter=":")
    medium = pd.read_csv("./benchmarkResults/medium" + str(i) + ".csv", header=None, delimiter=":")
    dom = pd.read_csv("./benchmarkResults/domlock" + str(i) + ".csv", header=None, delimiter=":")
    ca = pd.read_csv("./benchmarkResults/calock" + str(i) + ".csv", header=None, delimiter=":")
    mid = pd.read_csv("./benchmarkResults/mid" + str(i) + ".csv", header=None, delimiter=":")
    flexi = pd.read_csv("./benchmarkResults/flexi" + str(i) + ".csv", header=None, delimiter=":")
    intention = pd.read_csv("./benchmarkResults/intention" + str(i) + ".csv", header=None, delimiter=":")

    coarse = coarse.groupby(0).sum() / Iterations
    medium = medium.groupby(0).sum() / Iterations
    dom = dom.groupby(0).sum() / Iterations
    ca = ca.groupby(0).sum() / Iterations
    mid = mid.groupby(0).sum() / Iterations
    flexi = flexi.groupby(0).sum() / Iterations
    intention = intention.groupby(0).sum() / Iterations

    line = pd.DataFrame(
        {'ThreadCount': int(i), 'Coarse': coarse.iloc[2, 0], 'Medium': medium.iloc[2, 0], 'DomLock': dom.iloc[2, 0],
         'CALock': ca.iloc[2, 0], 'MID': mid.iloc[2, 0], 'FlexiGran': flexi.iloc[2, 0],
         'Intention Lock': intention.iloc[2, 0]}, index=[i])
    throughput = concat([throughput, line])
    line = pd.DataFrame(
        {'ThreadCount': int(i), 'Coarse': coarse.iloc[0, 0], 'Medium': medium.iloc[0, 0], 'DomLock': dom.iloc[0, 0],
         'CALock': ca.iloc[0, 0], 'MID': mid.iloc[0, 0], 'FlexiGran': flexi.iloc[0, 0],
         'Intention Lock': intention.iloc[0, 0]}, index=[i])
    idleness = concat([idleness, line])

    line = pd.DataFrame({'ThreadCount': int(i), 'Coarse': coarse.iloc[1, 0] + 0.1, 'Medium': medium.iloc[1, 0] + 0.1,
                         'DomLock': dom.iloc[1, 0], 'CALock': ca.iloc[1, 0], 'MID': mid.iloc[1, 0],
                         'FlexiGran': flexi.iloc[1, 0], 'Intention Lock': intention.iloc[1, 0] + 0.1}, index=[i])
    relabelling = concat([relabelling, line])
    i *= 2

order = {"Coarse": 0, "Medium": 1, "Intention Lock": 2, "DomLock": 3, "MID": 4, "FlexiGran": 5, "CALock": 6}

throughput = pd.melt(throughput, id_vars=['ThreadCount'],
                     value_vars=['Coarse', 'Medium', 'Intention Lock', 'DomLock', 'MID', 'FlexiGran', 'CALock'],
                     var_name='Lock Type',
                     value_name='Ops')
idleness = pd.melt(idleness, id_vars=['ThreadCount'],
                   value_vars=['Coarse', 'Medium', 'Intention Lock', 'DomLock', 'MID', 'FlexiGran', 'CALock'],
                   var_name='Lock Type',
                   value_name='Time')
relabelling = pd.melt(relabelling, id_vars=['ThreadCount'],
                      value_vars=['Coarse', 'Medium', 'Intention Lock', 'DomLock', 'MID', 'FlexiGran', 'CALock'],
                      var_name='Lock Type',
                      value_name='Time')

throughput["ThreadCount"] = throughput["ThreadCount"].astype(int)
idleness["ThreadCount"] = idleness["ThreadCount"].astype(int)
relabelling["ThreadCount"] = relabelling["ThreadCount"].astype(int)

throughput = throughput.sort_values(by=["Lock Type"], key=lambda x: x.map(order))
# print(throughput)
idleness = idleness.sort_values(by=["Lock Type"], key=lambda x: x.map(order))
relabelling = relabelling.sort_values(by=["Lock Type"], key=lambda x: x.map(order))

# retro = ["#ea5545", "#f46a9b", "#ef9b20", "#edbf33", "#ede15b", "#bdcf32", "#87bc45", "#27aeef", "#b33dc6"]
#
# dutch = ["#e60049","#0bb4ff", "#50e991", "#e6d800", "#9b19f5", "#ffa300", "#dc0ab4", "#b3d4ff", "#00bfa0"]
palette = [custom_colors[lock] for lock in throughput['Lock Type'].unique()]
sns.set_theme(style='whitegrid', palette=palette)
g = sns.catplot(x='ThreadCount', y='Ops', hue='Lock Type', data=throughput, kind='point', height=3, aspect=2,
                markers=["^", "o", "d", "x", "*", "+", "s"], linestyles=["-", "-", "--", "-.", "--", "-.", "-"])
g.despine()
g.set(yscale="linear", xlabel="Thread Count", ylabel="")
if "Read" in WorkloadType:
    g.set_ylabels('Op/s (logscale)')
if "WithoutModifications" in WorkloadType:
    plt.ylim(0, 350000)
else:
    plt.ylim(0, 200000)
g.legend.set_title("")
sns.move_legend(g, loc='upper center', ncols=4, fancybox=True, bbox_to_anchor=(0.45, 1.2))
plt.savefig("./benchmarkCharts/" + WorkloadType + "Throughput.png", dpi=300, bbox_inches="tight")




g = sns.catplot(x='ThreadCount', y='Time', hue='Lock Type', data=idleness, kind='point', height=3, aspect=2,
                markers=["^", "o", "d", "x", "*", "+", "s"])
g.despine()
g.set(yscale="log", xlabel="Thread Count", ylabel="")
if "Read" in WorkloadType:
    g.set_ylabels("Response time (ns logscale)")
g.legend.set_title("")
sns.move_legend(g, loc='upper center', ncols=4, fancybox=True, bbox_to_anchor=(0.45, 1.2))
plt.savefig("./benchmarkCharts/" + WorkloadType + "Idleness.png", dpi=300, bbox_inches="tight")




g = sns.catplot(x='ThreadCount', y='Time', hue='Lock Type', data=relabelling, kind='bar', height=3, aspect=2)
g.despine()
g.set(yscale="log", xlabel="Thread Count", ylabel="")
if "Read" in WorkloadType:
    g.set_ylabels("Relabelling time (ns logscale)")
g.legend.set_title("")
sns.move_legend(g, loc='upper center', ncols=4, fancybox=True, bbox_to_anchor=(0.45, 1.2))
plt.savefig("./benchmarkCharts/" + WorkloadType + "Relabelling.png", dpi=300, bbox_inches="tight")
