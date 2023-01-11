# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd


# Initialize the lists for X and Y
mediumCSTree = pd.read_csv('./dataForPlots/TreeCS.csv')
dfMT = pd.DataFrame(mediumCSTree)

# ax = plt.subplot(3,2,3, figsize=(15, 15))
plt.plot(dfMT['Domlock'], color='#ed553b', label='Domlock', marker='d')
plt.plot(dfMT['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
plt.plot(dfMT['CALock'], color='#173f5f', label='CALock', marker='+')
plt.set_xticks([0, 1, 2, 3, 4, 5, 6, 7], ['2', '4', '8', '16', '32', '64', '128', '256'])
plt.set_yscale("log")
plt.set_xlabel("No. of nodes locked")
plt.set_ylabel("Execution time(Log Scale)")
plt.legend()

plt.savefig('./NodesPerLockRequestTree.png')
