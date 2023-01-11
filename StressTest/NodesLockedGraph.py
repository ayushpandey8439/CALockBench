# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd


# Initialize the lists for X and Y
mediumCSGraph = pd.read_csv('./dataForPlots/GraphCS.csv')
dfMG = pd.DataFrame(mediumCSGraph)


# ax = plt.subplot(3,2,3, figsize=(15, 15))
plt.plot(dfMG['Domlock'], color='#ed553b', label='Domlock', marker='d')
plt.plot(dfMG['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
plt.plot(dfMG['CALock'], color='#173f5f', label='CALock', marker='+')
plt.set_xticks([0, 1, 2, 3, 4, 5], ['2', '4', '8', '16', '32', '64'])
plt.set_yscale("log")
plt.set_xlabel("No. of nodes locked")
plt.set_ylabel("Execution time(Log Scale)")
plt.legend()

plt.savefig('./NodesPerLockRequestGraph.png')
