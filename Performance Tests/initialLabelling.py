# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y

LockType = ("Small", "Medium", "Large")
DomLock =  (4.3501e+07,4.66862e+07,5.84065e+08)
CALock=( 4.36426e+08, 7.17528e+08,7.15851e+09)

x = np.arange(len(LockType))  # the label locations
width = 0.2  # the width of the bars


# # Add some text for labels, title and custom x-axis tick labels, etc.
# ax.set_ylabel('Label Assignment Time (ns logScale)')
# ax.set_xlabel('Size of the hierarchy')
# ax.set_xticks(x + width, LockType)
# ax.set_yscale("log")
# ax.legend()
#
# plt.show()
plt.rcParams['figure.figsize'] = [4.5, 2]
plt.bar(x, DomLock, width=width,color='#173f5f', label='Domlock')
plt.bar(x+width, CALock, width=width,color='#3caea3', label='CALock')
plt.xlabel('Hierarchy Size')
plt.ylabel('Time (ns logscale)')
plt.xticks([0,1,2], ['Small', 'Medium', 'Large'])
plt.yscale('log')
# # Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/InitialLabeling.png", dpi=300, bbox_inches="tight")