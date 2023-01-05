# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
# Initialize the lists for X and Y
data = pd.read_csv('./benchmarkResults/Results.csv')

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column


dft = df.T
print(df)
barWidth = 0

r1 = np.arange(len(df['ThreadCount']))
r2 = [x + barWidth for x in r1]
r3 = [x + barWidth for x in r2]
r4 = [x + barWidth for x in r3]

plt.plot(r1, df['Coarse'], color='#ed553b', label='Coarse', marker='d')
plt.plot(r2, df['Medium'], color='#f6d55c', label='Medium', marker='s')
plt.plot(r3, df['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(r4, df['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Op/s', fontweight='bold')

plt.xticks([r + barWidth for r in range(len(df['ThreadCount']))], ['1', '2', '4', '8', '16','32','64'])
# Create legend & Show graphic
plt.legend()
plt.savefig('./benchmarkResults/Results.png')
plt.show()