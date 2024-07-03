# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y

hierarchySize = ("Small", "Medium", "Large")
DomLock =  (19088,33264,33200)
CALock=(58064, 89804,89700)
MID = (28632,49896, 49800)



patterns = [ "//","\\\\","oo", "++","xx"]
width = 0.2

r1 = np.arange(len(hierarchySize)) # the label locations
r2 = [x + width for x in r1]
r3 = [x + width for x in r2]


# # Add some text for labels, title and custom x-axis tick labels, etc.
# ax.set_ylabel('Label Assignment Time (ns logScale)')
# ax.set_xlabel('Size of the hierarchy')
# ax.set_xticks(x + width, LockType)
# ax.set_yscale("log")
# ax.legend()
#
# plt.show()
# plt.rcParams['figure.figsize'] = [4.5, 2]
plt.bar(r1, DomLock, color='#7768AE', width=width, label='Domlock', edgecolor='black', hatch=patterns[2])
plt.bar(r2, CALock,  color='#3bb273', width=width, label='CALock', edgecolor='black', hatch=patterns[3])
plt.bar(r3, MID,     color='#4D9DE0', width=width, label='MID', edgecolor='black', hatch=patterns[4])
plt.xlabel('Hierarchy Size')
plt.ylabel('Metadata size (bytes)')
plt.xticks([0,1,2], ['Small', 'Medium', 'Large'])
# # Create legend & Show graphic
plt.grid(axis='y', linestyle='--', linewidth=0.5)

plt.legend(ncols=3)
plt.savefig("./benchmarkCharts/LabelsMemorySize.png", dpi=300, bbox_inches="tight")