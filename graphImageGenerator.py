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
barWidth = 0.2

r1 = np.arange(len(df['ThreadCount']))
r2 = [x + barWidth for x in r1]
r3 = [x + barWidth for x in r2]
r4 = [x + barWidth for x in r3]

plt.bar(r1, df['Coarse'], color='#D65780', width=barWidth, edgecolor='white', label='Coarse')
plt.bar(r2, df['Medium'], color='#A4B0F5', width=barWidth, edgecolor='white', label='Medium')
plt.bar(r3, df['Domlock'], color='#363537', width=barWidth, edgecolor='white', label='Domlock')
plt.bar(r4, df['CALock'], color='#ECA72C', width=barWidth, edgecolor='white', label='CALock')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Op/s', fontweight='bold')

plt.xticks([r + barWidth for r in range(len(df['ThreadCount']))], ['1', '2', '4', '8', '16','32','64'])
# Create legend & Show graphic
plt.legend()
plt.savefig('./benchmarkResults/Results.png')
plt.show()