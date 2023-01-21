import networkx as nx
import sys
import random
import csv

test_file = open('inputGraph/Graph.csv', 'w')
file_writer = csv.writer(test_file)

numNodes = sys.argv[1]
numConnectivity = sys.argv[2]

GC1 = nx.complete_graph(range(0,int(numNodes)), nx.DiGraph())
for i in range(len(list(GC1.edges))):
    file_writer.writerow([x for x in list(GC1.edges)[i]])
GC2 = nx.complete_graph(range(int(numNodes),2*int(numNodes)), nx.DiGraph())
for i in range(len(list(GC2.edges))):
    file_writer.writerow([x for x in list(GC2.edges)[i]])
GC3 = nx.complete_graph(range(2*int(numNodes),3*int(numNodes)), nx.DiGraph())
for i in range(len(list(GC3.edges))):
    file_writer.writerow([x for x in list(GC3.edges)[i]])
GC4 = nx.complete_graph(range(3*int(numNodes),4*int(numNodes)), nx.DiGraph())
for i in range(len(list(GC4.edges))):
    file_writer.writerow([x for x in list(GC4.edges)[i]])
GC5 = nx.complete_graph(range(4*int(numNodes),5*int(numNodes)), nx.DiGraph())
for i in range(len(list(GC5.edges))):
    file_writer.writerow([x for x in list(GC5.edges)[i]])

connectivityEdges= set()

for i in range(int(numConnectivity)):
    rs1 = random.choice(list(GC1.nodes()))
    rt2 = random.choice(list(GC2.nodes()))
    connectivityEdges.add((rs1, rt2))
    rs2 = random.choice(list(GC2.nodes()))
    rt3 = random.choice(list(GC3.nodes()))
    connectivityEdges.add((rs2, rt3))
    rs3 = random.choice(list(GC3.nodes()))
    rt4 = random.choice(list(GC4.nodes()))
    connectivityEdges.add((rs3, rt4))
    rs4 = random.choice(list(GC4.nodes()))
    rt5 = random.choice(list(GC5.nodes()))
    connectivityEdges.add((rs4, rt5))

for i in range(len(list(connectivityEdges))):
    file_writer.writerow([x for x in list(connectivityEdges)[i]])

print(len(connectivityEdges))
test_file.close()
