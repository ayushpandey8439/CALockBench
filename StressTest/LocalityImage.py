# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd


# Initialize the lists for X and Y
mediumCSTree = pd.read_csv('./dataForPlots/TreeCS.csv')
dfMT = pd.DataFrame(mediumCSTree)

# ax = plt.subplot(3,2,3, figsize=(15, 15))
plt.plot(dfMT['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(dfMT['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
plt.plot(dfMT['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xticks([0, 1, 2, 3, 4, 5, 6, 7], ['2', '4', '8', '16', '32', '64', '128', '256'])
#plt.yscale("log")
plt.xlabel("Vertices per lock request")
plt.ylabel("Execution time for 1K lock requests (ms)")
plt.legend()
# plt.title("1 thread \n consecutive nodes selected from leaves of a balanced binary tree\n with all paths known for Intention locking")

plt.savefig('./NodesPerLockRequestTree.png')
