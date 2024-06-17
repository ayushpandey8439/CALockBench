# Import the necessary modules
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
# Initialize the lists for X and Y
data = pd.read_csv("./benchmarkResults/Results.csv")

df = pd.DataFrame(data)
df.columns = df.columns.str.strip() #For column names
df.columns = [col.strip() for col in df.columns] #For data in each column

df.to_csv("./benchmarkCharts/ReadPercentageThroughput.csv", index=False)
plt.rcParams['figure.figsize'] = [4.5, 2]
plt.plot(df['Domlock']/1000000, color='#173f5f', label='Domlock', marker='+')
plt.plot(df['CALock']/1000000, color='#3caea3', label='CALock', marker='d')
plt.xlabel('Read Percentage')
plt.ylabel('Mil. Op/s')

plt.xticks([0,1,2,3,4,5,6,7,8], ['10', '20', '30', '40', '50','60','70','80','90'])

# Create legend & Show graphic
plt.legend()
plt.savefig("./benchmarkCharts/ReadPercentageThroughput.png",dpi=300,bbox_inches='tight')