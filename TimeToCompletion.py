import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

patterns = [ "//","\\\\","oo", "++","xx","--"]

data = [
    {"Operation": "Q1", "Coarse": 2, "Medium": 2, "DomLock": 819, "MID": 3460, "FlexiGran": 1468, "CALock": 10},
    {"Operation": "Q2", "Coarse": 2, "Medium": 2, "DomLock": 2287, "MID": 3564, "FlexiGran": 13086, "CALock": 34},
    {"Operation": "OP6", "Coarse": 2, "Medium": 2, "DomLock": 1557, "MID": 1652, "FlexiGran": 1604, "CALock": 18},
    {"Operation": "OP7", "Coarse": 2, "Medium": 2, "DomLock": 809, "MID": 1652, "FlexiGran": 1652, "CALock": 11},
    {"Operation": "OP9", "Coarse": 34, "Medium": 5, "DomLock": 1557, "MID": 3460, "FlexiGran": 2985, "CALock": 10},
    {"Operation": "OP10", "Coarse": 31, "Medium": 6, "DomLock": 1557, "MID": 5082, "FlexiGran": 14300, "CALock": 36},
    {"Operation": "SM2", "Coarse": 23, "Medium": 193, "DomLock": 791, "MID": 1652, "FlexiGran": 1604, "CALock": 2},
    {"Operation": "SM3", "Coarse": 25, "Medium": 248, "DomLock": 1557, "MID": 3460, "FlexiGran": 1702, "CALock": 19},
]

df=pd.DataFrame(data)

barwidth = 0.35

r1 = np.arange(8)*3
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]
r4 = [x + barwidth for x in r3]
r5 = [x + barwidth for x in r4]
r6 = [x + barwidth for x in r5]
r7 = [x + barwidth for x in r6]

plt.figure(figsize=(7, 4))

plt.bar(r1, df['Coarse'],  color='#E15554', width=barwidth, label='Coarse', edgecolor='black', hatch=patterns[0])
plt.bar(r2, df['Medium'],  color='#E1BC29', width=barwidth, label='Medium', edgecolor='black', hatch=patterns[1])
plt.bar(r3, df['DomLock'], color='#7768AE', width=barwidth, label='Domlock', edgecolor='black', hatch=patterns[2])
plt.bar(r4, df['MID'],     color='#4D9DE0', width=barwidth, label='MID', edgecolor='black', hatch=patterns[3])
plt.bar(r5, df['FlexiGran'],     color='#F9BA8F', width=barwidth, label='Flexigran 50%', edgecolor='black', hatch=patterns[4])
plt.bar(r6, df['CALock'],  color='#3bb273', width=barwidth, label='CALock', edgecolor='black', hatch=patterns[5])

plt.xlabel('Operation')
plt.ylabel('micros(logscale)')
plt.legend(loc='upper center', ncols=3, bbox_to_anchor=(0.5, 1.175), fancybox=True)
plt.yscale('log')
plt.xticks(r3, df['Operation'])
plt.grid(axis='y', linestyle='--', linewidth=0.5)
# plt.show()
plt.savefig("./benchmarkCharts/TTC.png",dpi=150, bbox_inches="tight")