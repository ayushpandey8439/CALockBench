# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd


# Initialize the lists for X and Y
mediumCSTree = pd.read_csv('./dataForPlots/TreeCS.csv')

mediumCSGraph = pd.read_csv('./dataForPlots/GraphCS.csv')
dfMT = pd.DataFrame(mediumCSTree)
dfMG = pd.DataFrame(mediumCSGraph)


fig, ax = plt.subplots(2, 1, figsize=(15, 15))

# ax = plt.subplot(3,2,3, figsize=(15, 15))
ax[0].plot(dfMT['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[0].plot(dfMT['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[0].plot(dfMT['CALock'], color='#173f5f', label='CALock', marker='+')
ax[0].set_title('Effect of Lock request size on trees(60 \u03BCs per request)')
ax[0].set_xticks([0, 1, 2, 3, 4, 5, 6, 7], ['2', '4', '8', '16', '32', '64', '128', '256'])
ax[0].set_yscale("log")
ax[0].set_xlabel("No. of nodes locked")
ax[0].set_ylabel("Execution time(Log Scale)")
ax[0].legend()


# ax = plt.subplot(3,2,3, figsize=(15, 15))
ax[1].plot(dfMG['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[1].plot(dfMG['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[1].plot(dfMG['CALock'], color='#173f5f', label='CALock', marker='+')
ax[1].set_title('Effect of Lock request size on Graphs(60 \u03BCs)')
ax[1].set_xticks([0, 1, 2, 3, 4, 5], ['2', '4', '8', '16', '32', '64'])
ax[1].set_yscale("log")
ax[0].set_xlabel("No. of nodes locked")
ax[0].set_ylabel("Execution time(Log Scale)")
ax[1].legend()

plt.savefig('./NodesPerLockRequest.png')
