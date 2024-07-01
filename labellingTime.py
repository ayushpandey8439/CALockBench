# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import sys

from pandas import concat

# print(sys.argv[1], sys.argv[2], sys.argv[3])
ThreadCount = int(sys.argv[1])
Iterations = int(sys.argv[2])
WorkloadType = sys.argv[3]

emptyDF = {'ThreadCount': [],'Coarse': [], 'Medium':[], 'Domlock':[], 'CALock':[], 'MID':[]}
throughput = pd.DataFrame(emptyDF)
idleness = pd.DataFrame(emptyDF)
relabelling = pd.DataFrame(emptyDF)
# read ThreadCount files
i=1
while i <= ThreadCount:
    print(i)
    coarse = pd.read_csv("./benchmarkResults/coarse"+str(i)+".csv", header=None, delimiter=":")
    medium = pd.read_csv("./benchmarkResults/medium"+str(i)+".csv", header=None, delimiter=":")
    dom = pd.read_csv("./benchmarkResults/domlock"+str(i)+".csv", header=None, delimiter=":")
    ca = pd.read_csv("./benchmarkResults/calock"+str(i)+".csv", header=None, delimiter=":")
    mid = pd.read_csv("./benchmarkResults/mid"+str(i)+".csv", header=None, delimiter=":")

    coarse = coarse.groupby(0).sum()/Iterations
    medium = medium.groupby(0).sum()/Iterations
    dom = dom.groupby(0).sum()/Iterations
    ca = ca.groupby(0).sum()/Iterations
    mid = mid.groupby(0).sum()/Iterations

    # print(coarse)
    # print(medium)
    # print(dom)
    # print(ca)
    # print(mid)
    line = pd.DataFrame({'ThreadCount':i, 'Coarse': coarse.iloc[0,0], 'Medium': medium.iloc[0,0], 'Domlock': dom.iloc[0,0], 'CALock': ca.iloc[0,0], 'MID': mid.iloc[0,0]}, index=[i])
    idleness = concat([idleness,line])
    line = pd.DataFrame({'ThreadCount':i, 'Coarse': coarse.iloc[2,0], 'Medium': medium.iloc[2,0], 'Domlock': dom.iloc[2,0], 'CALock': ca.iloc[2,0], 'MID': mid.iloc[2,0]}, index=[i])
    throughput = concat([throughput,line])
    line = pd.DataFrame({'ThreadCount':i, 'Coarse': coarse.iloc[1,0]+0.1, 'Medium': medium.iloc[1,0]+0.1, 'Domlock': dom.iloc[1,0], 'CALock': ca.iloc[1,0], 'MID': mid.iloc[1,0]}, index=[i])
    relabelling = concat([relabelling,line])
    i*=2

# print(idleness)
# print(throughput)
# print(relabelling)

plt.plot(throughput['Coarse'], color='#E15554', label='Coarse', marker='d')
plt.plot(throughput['Medium'], color='#E1BC29', label='Medium', marker='s')
plt.plot(throughput['Domlock'], color='#7768AE', label='Domlock', marker='+')
plt.plot(throughput['CALock'], color='#3bb273', label='CALock', marker='o')
plt.plot(throughput['MID'], color='#4D9DE0', label='MID', marker='x')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('Op/s', fontweight='bold')

plt.xticks(throughput['ThreadCount'])
# plt.ylim(-10000,350000)
# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+WorkloadType+"Throughput.png",dpi=150)

plt.figure()
plt.plot(idleness['Coarse'], color='#E15554', label='Coarse', marker='d')
plt.plot(idleness['Medium'], color='#E1BC29', label='Medium', marker='s')
plt.plot(idleness['Domlock'], color='#7768AE', label='Domlock', marker='+')
plt.plot(idleness['CALock'], color='#3bb273', label='CALock', marker='o')
plt.plot(idleness['MID'], color='#4D9DE0', label='MID', marker='x')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('ns', fontweight='bold')
plt.xticks(idleness['ThreadCount'])
if "Modifications" in WorkloadType:
    plt.ylim(-1000, 200000)
else:
    plt.ylim(-1000, 400000)
#
# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+WorkloadType+"Idleness.png",dpi=150)


plt.figure()
plt.plot(relabelling['Coarse'], color='#E15554', label='Coarse', marker='d')
plt.plot(relabelling['Medium'], color='#E1BC29', label='Medium', marker='s')
plt.plot(relabelling['Domlock'], color='#7768AE', label='Domlock', marker='+')
plt.plot(relabelling['CALock'], color='#3bb273', label='CALock', marker='o')
plt.plot(relabelling['MID'], color='#4D9DE0', label='MID', marker='x')
plt.xlabel('ThreadCount', fontweight='bold')
plt.ylabel('ns', fontweight='bold')
plt.xticks(relabelling['ThreadCount'])
plt.yscale('log')

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/"+WorkloadType+"Relabelling.png",dpi=150)



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
# plt.plot(df['Coarse'], color='#E15554', label='Coarse', marker='d')
# plt.plot(df['Medium'], color='#E1BC29', label='Medium', marker='s')
# plt.plot(df['Domlock'], color='#7768AE', label='Domlock', marker='+')
# plt.plot(df['CALock'], color='#4D9DE0', label='CALock', marker='o')
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
# plt.plot(df1['Domlock'], color='#7768AE', label='Domlock', marker='+')
# plt.plot(df1['CALock'], color='#4D9DE0', label='CALock', marker='o')
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
# plt.plot(df2['Domlock'], color='#7768AE', label='Domlock', marker='+')
# plt.plot(df2['CALock'], color='#4D9DE0', label='CALock', marker='o')
# plt.xlabel('ThreadCount', fontweight='bold')
# plt.ylabel('ns', fontweight='bold')
# plt.xticks(np.arange(0,threadCount+1), 2**np.arange(0,threadCount+1))
#
# # Create legend & Show graphic
# plt.legend()
# plt.savefig("./"+sys.argv[1]+"Relabelling.png",dpi=150)