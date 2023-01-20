# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y
data = pd.read_csv("./benchmarkResults/Results.csv")

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column

df.to_csv("./benchmarkCharts/"+sys.argv[1]+"Throughput.csv", index=False)


plt.plot(df['Coarse'], color='#ed553b', label='Coarse', marker='d')
plt.plot(df['Medium'], color='#f6d55c', label='Medium', marker='s')
plt.plot(df['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(df['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Op/s', fontweight='bold')

plt.xticks([0,1,2,3,4,5], ['1', '2', '4', '8', '16','32'])

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+sys.argv[1]+".png")