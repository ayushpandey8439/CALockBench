# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import sys
# Initialize the lists for X and Y
data = pd.read_csv("./benchmarkResults/Results.csv")
dataIdleness = pd.read_csv("./benchmarkResults/IdlenessResults.csv")

dataModifications= pd.read_csv("./benchmarkResults/ModificationResults.csv")

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column

df1 = pd.DataFrame(dataIdleness)
df1.columns = df1.columns.str.strip() #For column names
df1.columns = [col.strip() for col in df1.columns] #For data in each column

df2 = pd.DataFrame(dataModifications)
df2.columns = df2.columns.str.strip() #For column names
df2.columns = [col.strip() for col in df2.columns] #For data in each column

df.to_csv("./benchmarkCharts/"+sys.argv[1]+".csv", index=False)
df1.to_csv("./benchmarkCharts/"+sys.argv[1]+"Idleness.csv", index=False)
print(df)
print(df1)

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
plt.savefig("./benchmarkCharts/"+sys.argv[1]+".png")

plt.figure()

plt.plot(df1['Domlock'], color='#ed553b', label='Domlock', marker='d')
plt.plot(df1['CALock'], color='#173f5f', label='CALock', marker='+')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Time spent waiting for lock', fontweight='bold')
plt.yscale("log")
plt.xticks([0,1,2,3,4,5], ['1', '2', '4', '8', '16','32'])

plt.legend()
plt.savefig("./benchmarkCharts/"+sys.argv[1]+"Idleness.png")

plt.figure()

plt.plot(df2['Domlock'], color='#ed553b', label='Domlock', marker='d')
plt.plot(df2['CALock'], color='#173f5f', label='CALock', marker='+')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Time spent relabelling', fontweight='bold')
plt.yscale("log")
plt.xticks([0,1,2,3,4,5], ['1', '2', '4', '8', '16','32'])

plt.legend()
plt.savefig("./benchmarkCharts/"+sys.argv[1]+"Modifications.png")