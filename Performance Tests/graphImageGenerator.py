# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y
data = pd.read_csv("./benchmarkResults/Results.csv")
data1 = pd.read_csv("./benchmarkResults/IdlenessResults.csv")
data2 = pd.read_csv("./benchmarkResults/RelabellingResults.csv")
threadCount = int(sys.argv[2])+1

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column

df.to_csv("./benchmarkCharts/"+sys.argv[1]+"Throughput.csv", index=False)


df1 = pd.DataFrame(data1)
df1.columns = df1.columns.str.strip() #For column names
df1.columns = [col.strip() for col in df1.columns] #For data in each column

df1.to_csv("./benchmarkCharts/"+sys.argv[1]+"Idleness.csv", index=False)


df2 = pd.DataFrame(data2)
df2.columns = df2.columns.str.strip() #For column names
df2.columns = [col.strip() for col in df2.columns] #For data in each column

df2.to_csv("./benchmarkCharts/"+sys.argv[1]+"Relabelling.csv", index=False)



plt.plot(df['Coarse'], color='#ed553b', label='Coarse', marker='d')
plt.plot(df['Medium'], color='#f6d55c', label='Medium', marker='s')
plt.plot(df['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(df['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Op/s', fontweight='bold')

plt.xticks(np.arange(0,threadCount), 2**np.arange(0,threadCount))

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+sys.argv[1]+"Throughput.png")

plt.figure()

plt.plot(df['Coarse'], color='#ed553b', label='Coarse', marker='d')
plt.plot(df['Medium'], color='#f6d55c', label='Medium', marker='s')
plt.plot(df1['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(df1['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('ns', fontweight='bold')
plt.xticks(np.arange(0,threadCount), 2**np.arange(0,threadCount))

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+sys.argv[1]+"Idleness.png")


plt.figure()
plt.plot(df2['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(df2['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('ns', fontweight='bold')
plt.xticks(np.arange(0,threadCount), 2**np.arange(0,threadCount))

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+sys.argv[1]+"Relabelling.png")