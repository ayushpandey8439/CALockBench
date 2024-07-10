# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys

from pandas import concat

# print(sys.argv[1], sys.argv[2], sys.argv[3])
ThreadCount = int(sys.argv[1])
Iterations = int(sys.argv[2])
WorkloadType = sys.argv[3]

patterns = ["//", "\\\\", "oo", "++", "xx", "--"]

emptyDF = {'ThreadCount': [], 'Coarse': [], 'Medium': [], 'Domlock': [], 'CALock': [], 'MID': [], 'Flexigran': []}
throughput = pd.DataFrame(emptyDF)
idleness = pd.DataFrame(emptyDF)
relabelling = pd.DataFrame(emptyDF)
# read ThreadCount files
i = 1
while i <= ThreadCount:
    print(i)
    coarse = pd.read_csv("./benchmarkResults/coarse" + str(i) + ".csv", header=None, delimiter=":")
    medium = pd.read_csv("./benchmarkResults/medium" + str(i) + ".csv", header=None, delimiter=":")
    dom = pd.read_csv("./benchmarkResults/domlock" + str(i) + ".csv", header=None, delimiter=":")
    ca = pd.read_csv("./benchmarkResults/calock" + str(i) + ".csv", header=None, delimiter=":")
    mid = pd.read_csv("./benchmarkResults/mid" + str(i) + ".csv", header=None, delimiter=":")
    flexi = pd.read_csv("./benchmarkResults/flexi" + str(i) + ".csv", header=None, delimiter=":")

    coarse = coarse.groupby(0).sum() / Iterations
    medium = medium.groupby(0).sum() / Iterations
    dom = dom.groupby(0).sum() / Iterations
    ca = ca.groupby(0).sum() / Iterations
    mid = mid.groupby(0).sum() / Iterations
    flexi = flexi.groupby(0).sum() / Iterations

    # print(coarse)
    # print(medium)
    # print(dom)
    # print(ca)
    # print(mid)
    line = pd.DataFrame(
        {'ThreadCount': i, 'Coarse': coarse.iloc[0, 0], 'Medium': medium.iloc[0, 0], 'Domlock': dom.iloc[0, 0],
         'CALock': ca.iloc[0, 0], 'MID': mid.iloc[0, 0], 'Flexigran': flexi.iloc[0, 0]}, index=[i])
    idleness = concat([idleness, line])
    line = pd.DataFrame(
        {'ThreadCount': i, 'Coarse': coarse.iloc[2, 0], 'Medium': medium.iloc[2, 0], 'Domlock': dom.iloc[2, 0],
         'CALock': ca.iloc[2, 0], 'MID': mid.iloc[2, 0], 'Flexigran': flexi.iloc[2, 0]}, index=[i])
    throughput = concat([throughput, line])
    line = pd.DataFrame({'ThreadCount': i, 'Coarse': coarse.iloc[1, 0] + 0.1, 'Medium': medium.iloc[1, 0] + 0.1,
                         'Domlock': dom.iloc[1, 0], 'CALock': ca.iloc[1, 0], 'MID': mid.iloc[1, 0],
                         'Flexigran': flexi.iloc[1, 0]}, index=[i])
    relabelling = concat([relabelling, line])
    i *= 2

# print(idleness)
# print(throughput)
# print(relabelling)

barwidth = 0.35

r1 = np.arange(len(throughput['ThreadCount'])) * 3
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]
r4 = [x + barwidth for x in r3]
r5 = [x + barwidth for x in r4]
r6 = [x + barwidth for x in r5]
r7 = [x + barwidth for x in r6]

# print(throughput)

plt.figure(figsize=(7, 4))
plt.bar(r1, throughput['Coarse'], color='#E15554', width=barwidth, label='Coarse', edgecolor='black', hatch=patterns[0])
plt.bar(r2, throughput['Medium'], color='#E1BC29', width=barwidth, label='Medium', edgecolor='black', hatch=patterns[1])
plt.bar(r3, throughput['Domlock'], color='#7768AE', width=barwidth, label='Domlock', edgecolor='black',
        hatch=patterns[2])
plt.bar(r4, throughput['MID'], color='#4D9DE0', width=barwidth, label='MID', edgecolor='black', hatch=patterns[3])
plt.bar(r5, throughput['Flexigran'], color='#F9BA8F', width=barwidth, label='Flexigran 50%', edgecolor='black',
        hatch=patterns[4])
plt.bar(r6, throughput['CALock'], color='#3bb273', width=barwidth, label='CALock', edgecolor='black', hatch=patterns[5])
plt.xlabel('Threads')
if "Read" in WorkloadType:
    plt.ylabel('Op/s')
if "WithoutModifications" in WorkloadType:
    plt.ylim(0, 350000)
else:
    plt.ylim(0, 200000)

plt.legend(loc='upper center', ncols=3, bbox_to_anchor=(0.5, 1.175), fancybox=True)
plt.xticks(r3, throughput['ThreadCount'].apply(lambda x: int(x)))
plt.grid(axis='y', linestyle='--', linewidth=0.5)
plt.savefig("./benchmarkCharts/" + WorkloadType + "Throughput.png", dpi=300)

plt.figure(figsize=(7, 4))
plt.bar(r1, idleness['Coarse'], color='#E15554', width=barwidth, label='Coarse', edgecolor='black', hatch=patterns[0])
plt.bar(r2, idleness['Medium'], color='#E1BC29', width=barwidth, label='Medium', edgecolor='black', hatch=patterns[1])
plt.bar(r3, idleness['Domlock'], color='#7768AE', width=barwidth, label='Domlock', edgecolor='black', hatch=patterns[2])
plt.bar(r4, idleness['MID'], color='#4D9DE0', width=barwidth, label='MID', edgecolor='black', hatch=patterns[3])
plt.bar(r5, idleness['Flexigran'], color='#F9BA8F', width=barwidth, label='Flexigran 50%', edgecolor='black',
        hatch=patterns[4])
plt.bar(r6, idleness['CALock'], color='#3bb273', width=barwidth, label='CALock', edgecolor='black', hatch=patterns[5])
plt.xlabel('Threads')
if "Read" in WorkloadType:
    plt.ylabel('$\mu$s(logscale)')

plt.yscale('log')
plt.xticks(r3, idleness['ThreadCount'].apply(lambda x: int(x)))
plt.grid(axis='y', linestyle='--', linewidth=0.5)
plt.legend(loc='upper center', ncols=3, bbox_to_anchor=(0.5, 1.175), fancybox=True)
plt.savefig("./benchmarkCharts/" + WorkloadType + "Idleness.png", dpi=150)

plt.figure(figsize=(7, 4))
plt.bar(r1, relabelling['Coarse'], color='#E15554', width=barwidth, label='Coarse', edgecolor='black',
        hatch=patterns[0])
plt.bar(r2, relabelling['Medium'], color='#E1BC29', width=barwidth, label='Medium', edgecolor='black',
        hatch=patterns[1])
plt.bar(r3, relabelling['Domlock'], color='#7768AE', width=barwidth, label='Domlock', edgecolor='black',
        hatch=patterns[2])
plt.bar(r4, relabelling['MID'], color='#4D9DE0', width=barwidth, label='MID', edgecolor='black', hatch=patterns[3])
plt.bar(r5, relabelling['Flexigran'], color='#F9BA8F', width=barwidth, label='Flexigran 50%', edgecolor='black',
        hatch=patterns[4])
plt.bar(r6, relabelling['CALock'], color='#3bb273', width=barwidth, label='CALock', edgecolor='black',
        hatch=patterns[5])
plt.xlabel('Threads')
if "Read" in WorkloadType:
    plt.ylabel('ns(logscale)')

plt.legend(loc='upper center', ncols=3, bbox_to_anchor=(0.5, 1.175), fancybox=True)
plt.xticks(r3, relabelling['ThreadCount'].apply(lambda x: int(x)))
plt.grid(axis='y', linestyle='--', linewidth=0.5)
plt.yscale('log')
plt.savefig("./benchmarkCharts/" + WorkloadType + "Relabelling.png", dpi=300)

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
