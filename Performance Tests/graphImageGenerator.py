# Import the necessary modules
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
import pandas as pd
import numpy as np
import sys


def makeChart(loadType):
    if(loadType in ["ReadWithoutModifications", "WriteWithoutModifications", "BalancedWithoutModifications"]):
        throughputTicks = np.arange(0,300000,100000)
        idlenessTicks = np.arange(0,30000,5000)
    else :
        throughputTicks = np.arange(0,120000,50000)
        idlenessTicks = np.arange(0,80000,10000)

    # Initialize the lists for X and Y
    data = pd.read_csv("./benchmarkResults/Results.csv")
    data1 = pd.read_csv("./benchmarkResults/IdlenessResults.csv")
    data2 = pd.read_csv("./benchmarkResults/RelabellingResults.csv")

    threadCount = int(sys.argv[2])+1
    #
    df = pd.DataFrame(data)
    df = df.head(threadCount)
    df.columns = df.columns.str.strip() #For column names
    df.columns = [col.strip() for col in df.columns] #For data in each column
    df.to_csv("./benchmarkCharts/"+loadType+"Throughput.csv", index=False)


    df1 = pd.DataFrame(data1)
    df1 = df1.head(threadCount)
    df1.columns = df1.columns.str.strip() #For column names
    df1.columns = [col.strip() for col in df1.columns] #For data in each column
    df1.to_csv("./benchmarkCharts/"+loadType+"Idleness.csv", index=False)



    df2 = pd.DataFrame(data2)
    df2 =df2.head(threadCount)
    df2.columns = df2.columns.str.strip() #For column names
    df2.columns = [col.strip() for col in df2.columns] #For data in each column
    df2.to_csv("./benchmarkCharts/"+loadType+"Relabeling.csv", index=False)


    plt.rcParams['figure.figsize'] = [4.5, 2]
    plt.figure()
    plt.plot(df1['Coarse'],df['Coarse'],  color='#ed553b', label='Coarse', marker='x', markersize=5, linewidth=1)
    plt.plot(df1['Medium'],df['Medium'], color='#f6d55c', label='Medium', marker='o', markersize=5, linewidth=1)
    plt.plot(df1['Domlock'],df['Domlock'], color='#173f5f', label='Domlock', marker='+', markersize=5, linewidth=1)
    plt.plot(df1['CALock'],df['CALock'], color='#3caea3', label='CALock', marker='d', markersize=5, linewidth=1)

    plt.ylabel("Throughput (Kop/s)")
    plt.xlabel("Latency (logscale \u03BCs)")
    plt.xscale('log')
    plt.yticks(throughputTicks, throughputTicks/1000, fontsize=12)
    plt.legend(fontsize="8")
    plt.savefig("./benchmarkCharts/"+loadType+".png",dpi=200,bbox_inches='tight')
    
    plt.figure()
    plt.plot(df2['Domlock'], color='#173f5f', label='Domlock', marker='+', linewidth=1,markerfacecolor='none')
    plt.plot(df2['CALock'], color='#3caea3', label='CALock', marker='o', linewidth=1,markerfacecolor='none')
    plt.yscale('log')
    plt.xticks(np.arange(0,threadCount), 2**np.arange(0,threadCount),  fontsize=12)
    if(loadType=="ReadWithModifications"):
        plt.ylabel("\u03BCs (logscale)", fontsize=20)
    plt.legend()
    plt.xlabel("Threads")
    # Create legend & Show graphic

    plt.savefig("./benchmarkCharts/"+loadType+"Relabeling.png",dpi=200,bbox_inches='tight')


def millions_formatter(x, pos):
    return f'{x / 1000000}'

makeChart(sys.argv[1])

