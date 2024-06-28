# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys

print(sys.argv[1], sys.argv[2], sys.argv[3])
ThreadCount = int(sys.argv[1])
Iterations = int(sys.argv[2])
WorkloadType = sys.argv[3]



#
# # Initialize the lists for X and Y
# data = pd.read_csv("./BlockingResults/"+sys.argv[1]+"/"+sys.argv[1]+"Throughput.csv")
#
# data1 = pd.read_csv("./BlockingResults/"+sys.argv[1]+"/"+sys.argv[1]+"Idleness.csv")
# data2 = pd.read_csv("./BlockingResults/"+sys.argv[1]+"/"+sys.argv[1]+"Relabelling.csv")
# threadCount = 5
# #
# df = pd.DataFrame(data)
# df.columns = df.columns.str.strip() #For column names
# df.columns = [col.strip() for col in df.columns] #For data in each column
#
# # df.to_csv("./benchmarkCharts/"+sys.argv[1]+"Throughput.csv", index=False)
#
#
# df1 = pd.DataFrame(data1)
# df1.columns = df1.columns.str.strip() #For column names
# df1.columns = [col.strip() for col in df1.columns] #For data in each column
#
# # df1.to_csv("./benchmarkCharts/"+sys.argv[1]+"Idleness.csv", index=False)
#
#
# df2 = pd.DataFrame(data2)
# df2.columns = df2.columns.str.strip() #For column names
# df2.columns = [col.strip() for col in df2.columns] #For data in each column
#
# # df2.to_csv("./benchmarkCharts/"+sys.argv[1]+"Relabelling.csv", index=False)
#
#
#
# plt.plot(df['Coarse'], color='#ed553b', label='Coarse', marker='d')
# plt.plot(df['Medium'], color='#f6d55c', label='Medium', marker='s')
# plt.plot(df['Domlock'], color='#173f5f', label='Domlock', marker='+')
# plt.plot(df['CALock'], color='#3caea3', label='CALock', marker='o')
# plt.xlabel('ThreadCount', fontweight='bold')
# plt.ylabel('Op/s', fontweight='bold')
#
# plt.xticks(np.arange(0,threadCount+1), 2**np.arange(0,threadCount+1))
# plt.ylim(-10000,350000)
# # Create legend & Show graphic
# plt.legend()
# plt.savefig("./"+sys.argv[1]+"Throughput.png",dpi=150)
#
# plt.figure()
# plt.plot(df1['Domlock'], color='#173f5f', label='Domlock', marker='+')
# plt.plot(df1['CALock'], color='#3caea3', label='CALock', marker='o')
# plt.xlabel('ThreadCount', fontweight='bold')
# plt.ylabel('ns', fontweight='bold')
# plt.xticks(np.arange(0,threadCount+1), 2**np.arange(0,threadCount+1))
# plt.ylim(-1000, 60000)
# # Create legend & Show graphic
# plt.legend()
# plt.savefig("./"+sys.argv[1]+"Idleness.png",dpi=150)
#
#
# plt.figure()
# plt.plot(df2['Domlock'], color='#173f5f', label='Domlock', marker='+')
# plt.plot(df2['CALock'], color='#3caea3', label='CALock', marker='o')
# plt.xlabel('ThreadCount', fontweight='bold')
# plt.ylabel('ns', fontweight='bold')
# plt.xticks(np.arange(0,threadCount+1), 2**np.arange(0,threadCount+1))
#
# # Create legend & Show graphic
# plt.legend()
# plt.savefig("./"+sys.argv[1]+"Relabelling.png",dpi=150)