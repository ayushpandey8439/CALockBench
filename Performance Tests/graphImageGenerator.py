# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import sys
# Initialize the lists for X and Y
data = pd.read_csv(sys.argv[1])

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column
df.to_csv("./benchmarkCharts/"+sys.argv[2]+".csv", index=False)
print(df)
barWidth = 0

plt.plot(df['Coarse'], color='#f6d55c', label='Coarse', marker='s')
plt.plot(df['Medium'], color='#4cBB17', label='Medium', marker='o')
plt.plot(df['Domlock'], color='#ed553b', label='Domlock', marker='d')
plt.plot(df['CALock'], color='#173f5f', label='CALock', marker='+')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Throughput(Op/s)', fontweight='bold')
plt.ylim(-9000,320000)
plt.xticks([0,1,2,3,4,5], ['1', '2', '4', '8', '16','32'])

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+sys.argv[2]+".png")
