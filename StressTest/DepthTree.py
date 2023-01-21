# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd


# Initialize the lists for X and Y
mediumCSTree = pd.read_csv('./dataForPlots/TreeDepth.csv')
dfMT = pd.DataFrame(mediumCSTree)

# ax = plt.subplot(3,2,3, figsize=(15, 15))
plt.plot(dfMT['Domlock'], color='#173f5f', label='Domlock', marker='+')
plt.plot(dfMT['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
plt.plot(dfMT['CALock'], color='#3caea3', label='CALock', marker='o')
plt.xticks([0, 1, 2, 3, 4, 5, 6, 7,8,9,10], ['20', '21', '22', '23', '24', '25', '26', '27','28','29','30'])
plt.xlabel("Depth of hierarchy(Number of nodes in power of 2)")
plt.ylabel("Execution time")
plt.legend()

plt.savefig('./DepthOfTree.png')
