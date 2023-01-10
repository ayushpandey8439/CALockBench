import matplotlib.pyplot as plt
import pandas as pd

skewness = pd.read_csv('./dataForPlots/Skewness.csv')

dfskewness = pd.DataFrame(skewness)

# ax = plt.subplot(3,2,5, figsize=(15, 15))
plt.plot(dfskewness['Domlock'], color='#ed553b', label='Domlock', marker='d')
plt.plot(dfskewness['Intention Lock'], color='#f6d55c', label='Intention Lock', marker='s')
plt.plot(dfskewness['CALock'], color='#173f5f', label='CALock', marker='+')
plt.title('Skewness of vertex selection for locking(60 \u03BCs per request)')
plt.xticks([0, 1, 2, 3, 4, 5, 6, 7], ['1', '2', '4', '8', '16', '32', '64', '128'])
plt.xlabel("No. of buckets")
plt.ylabel("Execution time(Log Scale)")
plt.legend()
plt.savefig('./Skewness.png')