import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

patterns = [ "//","\\\\","oo", "++","xx","--"]

data = [
    {"Operation": "Q1", "Coarse": 35, "Medium": 11, "DomLock": 560, "MID": 1, "FlexiGran": 589, "CALock": 3},
    {"Operation": "Q2", "Coarse": 43, "Medium": 11, "DomLock": 1092, "MID": 3564, "FlexiGran": 1125, "CALock": 11},
    {"Operation": "OP6", "Coarse": 32, "Medium": 6, "DomLock": 560, "MID": 1, "FlexiGran": 6, "CALock": 4},
    {"Operation": "OP7", "Coarse": 21, "Medium": 1, "DomLock": 553, "MID": 1, "FlexiGran": 7, "CALock": 5},
    {"Operation": "OP9", "Coarse": 34, "Medium": 3, "DomLock": 1, "MID": 1, "FlexiGran": 3, "CALock": 3},
    {"Operation": "OP10", "Coarse": 31, "Medium": 11, "DomLock": 1092, "MID": 1229, "FlexiGran": 1092, "CALock": 15},
    {"Operation": "SM2", "Coarse": 1, "Medium": 6, "DomLock": 556, "MID": 2427, "FlexiGran": 592, "CALock": 2},
    {"Operation": "SM3", "Coarse": 1, "Medium": 1, "DomLock": 560, "MID": 1266, "FlexiGran": 590, "CALock": 7},
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
plt.savefig("./benchmarkCharts/TTC.png",dpi=150)