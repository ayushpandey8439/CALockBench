# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y
data = pd.read_csv("./benchmarkResults/containment.csv")

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column

df.to_csv("./benchmarkCharts/ContainmentRatio.csv", index=False)

x = df.groupby('Type', as_index=False).agg('mean')
print(x)


plt.plot(x['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(x['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xlabel('Vertex type', fontweight='bold')
plt.ylabel('Vertices locked (LogScale)', fontweight='bold')

plt.xticks([0,1,2,3], ['Complex Assembly', 'Base Assembly', 'Composite Part', 'Atomic Part'])
plt.yscale('log')
# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/ContainmentRatio.png")