# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y

LockType = ("Small", "Medium", "Large")
DomLock =  (19088,33136,33328)
CALock=( 28632, 49704,49992)

x = np.arange(len(LockType))  # the label locations
width = 0.2  # the width of the bar
plt.rcParams['figure.figsize'] = [4.5, 1.5]
plt.bar(x, DomLock, width=width,color='#173f5f', label='Domlock')
plt.bar(x+width, CALock, width=width,color='#3caea3', label='CALock')
plt.xlabel('Hierarchy Size')
plt.ylabel('Memory (bytes)')
plt.xticks([0,1,2], ['Small', 'Medium', 'Large'])
plt.ylim(ymin=15000)
# plt.yscale('log')
# # Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/LabelsMemorySize.png", bbox_inches='tight', dpi=300)