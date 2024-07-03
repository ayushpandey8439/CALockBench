# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y
data = pd.read_csv("./benchmarkResults/containment.csv")
patterns = [ "//","\\\\","oo", "++","xx"]

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column

# df.to_csv("./benchmarkCharts/ContainmentRatio.csv", index=False)

containment = df.groupby('Type', as_index=False).agg('mean')
print(containment)


width = 0.2
r1 = np.arange(len(containment['Type'])) # the label locations
r2 = [x + width for x in r1]
r3 = [x + width for x in r2]

plt.bar(r1, containment["Domlock"], color='#7768AE', width=width, label='Domlock', edgecolor='black', hatch=patterns[2])
plt.bar(r2, containment["CALock"],  color='#3bb273', width=width, label='CALock', edgecolor='black', hatch=patterns[3])
plt.bar(r3, containment["MID"],     color='#4D9DE0', width=width, label='MID', edgecolor='black', hatch=patterns[4])

plt.xlabel('Vertex type', fontweight='bold')
plt.ylabel('Vertices locked (log scale)', fontweight='bold')

plt.xticks([0,1,2,3], ['Complex Assembly', 'Base Assembly', 'Composite Part', 'Atomic Part'])
plt.yscale('log')
plt.grid(axis='y', linestyle='--', linewidth=0.5)

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/ContainmentRatio.png")