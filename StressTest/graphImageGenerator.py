# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Initialize the lists for X and Y
smallCSTree = pd.read_csv('./dataForPlots/TreeSmallCS.csv')
mediumCSTree = pd.read_csv('./dataForPlots/TreeMediumCS.csv')
largeCSTree = pd.read_csv('./dataForPlots/TreeLargeCS.csv')

smallCSGraph = pd.read_csv('./dataForPlots/GraphSmallCS.csv')
mediumCSGraph = pd.read_csv('./dataForPlots/GraphMediumCS.csv')
largeCSGraph = pd.read_csv('./dataForPlots/GraphLargeCS.csv')

skewness = pd.read_csv('./dataForPlots/Skewness.csv')

dfST = pd.DataFrame(smallCSTree)
dfMT = pd.DataFrame(mediumCSTree)
dfLT = pd.DataFrame(largeCSTree)

dfSG = pd.DataFrame(smallCSGraph)
dfMG = pd.DataFrame(mediumCSGraph)
dfLG = pd.DataFrame(largeCSGraph)

dfskewness = pd.DataFrame(skewness)

fig, ax = plt.subplots(3, 2, figsize=(15, 15))

# ax = plt.subplot(3,2,1, figsize=(15, 15));
ax[0, 0].plot(dfST['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[0, 0].plot(dfST['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[0, 0].plot(dfST['CALock'], color='#173f5f', label='CALock', marker='+')
ax[0, 0].set_title('Small Critical Section on Trees(6 \u03BCs)')
ax[0, 0].set_xticks([0, 1, 2, 3, 4, 5, 6, 7], ['2', '4', '8', '16', '32', '64', '128', '256'])
ax[0,0].set_ylim(0,1)
ax[0, 0].legend()

# ax = plt.subplot(3,2,3, figsize=(15, 15))
ax[1, 0].plot(dfMT['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[1, 0].plot(dfMT['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[1, 0].plot(dfMT['CALock'], color='#173f5f', label='CALock', marker='+')
ax[1, 0].set_title('Medium Critical Section on Trees(60 \u03BCs)')
ax[1, 0].set_xticks([0, 1, 2, 3, 4, 5, 6, 7], ['2', '4', '8', '16', '32', '64', '128', '256'])
ax[1,0].set_ylim(0,1)
ax[1, 0].legend()

# ax = plt.subplot(3,2,5, figsize=(15, 15))
ax[2, 0].plot(dfLT['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[2, 0].plot(dfLT['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[2, 0].plot(dfLT['CALock'], color='#173f5f', label='CALock', marker='+')
ax[2, 0].set_title('Large Critical Section on Trees(600 \u03BCs)')
ax[2, 0].set_xticks([0, 1, 2, 3, 4, 5, 6, 7], ['2', '4', '8', '16', '32', '64', '128', '256'])
ax[2,0].set_ylim(0,1)
ax[2, 0].legend()

# ax = plt.subplot(3,2,1, figsize=(15, 15));
ax[0, 1].plot(dfSG['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[0, 1].plot(dfSG['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[0, 1].plot(dfSG['CALock'], color='#173f5f', label='CALock', marker='+')
ax[0, 1].set_title('Small Critical Section on Graphs(6 \u03BCs)')
ax[0, 1].set_xticks([0, 1, 2, 3, 4, 5], ['2', '4', '8', '16', '32', '64'])
ax[0, 1].legend()

# ax = plt.subplot(3,2,3, figsize=(15, 15))
ax[1, 1].plot(dfMG['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[1, 1].plot(dfMG['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[1, 1].plot(dfMG['CALock'], color='#173f5f', label='CALock', marker='+')
ax[1, 1].set_title('Medium Critical Section on Graphs(60 \u03BCs)')
ax[1, 1].set_xticks([0, 1, 2, 3, 4, 5], ['2', '4', '8', '16', '32', '64'])
ax[1, 1].legend()

# ax = plt.subplot(3,2,5, figsize=(15, 15))
ax[2, 1].plot(dfLG['Domlock'], color='#ed553b', label='Domlock', marker='d')
ax[2, 1].plot(dfLG['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
ax[2, 1].plot(dfLG['CALock'], color='#173f5f', label='CALock', marker='+')
ax[2, 1].set_title('Large Critical Section on Graphs (600 \u03BCs)')
ax[2, 1].set_xticks([0, 1, 2, 3, 4, 5], ['2', '4', '8', '16', '32', '64'])

ax[2, 1].legend()

plt.savefig('./Nodesused.png')

# ax = plt.subplot(3,2,5, figsize=(15, 15))
plt.plot(dfskewness['Domlock'], color='#ed553b', label='Domlock', marker='d')
plt.plot(dfskewness['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
plt.plot(dfskewness['CALock'], color='#173f5f', label='CALock', marker='+')
plt.title('Skewness of vertex selection (Medium critical section 60 \u03BCs)')
plt.xticks([0, 1, 2, 3, 4, 5, 6, 7], ['1', '2', '4', '8', '16', '32', '64', '128'])

plt.legend()
plt.savefig('./Skewness.png')
#
# barWidth = 0
#
# r1 = np.arange(len(df['ThreadCount']))
# r2 = [x + barWidth for x in r1]
# r3 = [x + barWidth for x in r2]
# r4 = [x + barWidth for x in r3]
#
# plt.plot(r1, df['Coarse'], color='#ed553b', label='Coarse', marker='d')
# plt.plot(r2, df['Medium'], color='#f6d55c', label='Medium', marker='s')
# plt.plot(r3, df['Domlock'], color='#173f5f', label='Domlock', marker='+')
# plt.plot(r4, df['CALock'], color='#3caea3', label='CALock', marker='o')
# plt.xlabel('ThreadCount', fontweight='bold')
# plt.ylabel('Op/s', fontweight='bold')
#
# # Create legend & Show graphic
#
# plt.show()