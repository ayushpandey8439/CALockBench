//
// Created by pandey on 18/06/24.
//

#include <fstream>
#include "output.h"
#include "../struct/connection.h"
int output::run(int tid) const {
    queue<ComplexAssembly *> cassmQ;
    queue<BaseAssembly *> bassmQ;
    queue<CompositePart *> cpartQ;
    queue<AtomicPart *> apartQ;

    string graphPath = "./graph.gv";
    if (graphPath.empty()) {
        throw invalid_argument("Graph path not found in config file");
    }
    std::ofstream graph;
    graph.open(graphPath, ios::out);
    if (!graph.is_open()) {
        throw runtime_error("Error opening graph output file");
    }
    graph << "digraph G {" << endl;

    Set<DesignObj *> visitedAssemblies;
    ComplexAssembly *root = dataHolder->getModule()->getDesignRoot();
    cassmQ.push(root);


    while (!cassmQ.empty()) {
        traverse(cassmQ.front(), &cassmQ, &bassmQ, &visitedAssemblies, &graph);
        cassmQ.pop();
    }
    while (!bassmQ.empty()) {
        traverse(bassmQ.front(), &cpartQ, &visitedAssemblies, &graph);
        bassmQ.pop();
    }
    while (!cpartQ.empty()) {
        traverse(cpartQ.front(), &apartQ, &visitedAssemblies, &graph);
        cpartQ.pop();
    }
    graph << "}" << endl;
    graph.close();
    return 0;

}

void output::traverse(ComplexAssembly *complexAssembly, queue<ComplexAssembly *> *cassmQ,
                      std::queue<BaseAssembly *> *bassmQ, Set<DesignObj *> *visited, ofstream *graph) const {
    if(visited->contains(complexAssembly)){
        return;
    }
    visited->add(complexAssembly);
    *graph << complexAssembly->getId() << " [label=\"" << complexAssembly->getId() << "\n" << complexAssembly->getPathLabel() << "\"];" << endl;
    Set<Assembly *> *subAssm = complexAssembly->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = complexAssembly->areChildrenBaseAssemblies();

    while(iter.has_next()) {
        Assembly *assm = iter.next();
        *graph << complexAssembly->getId() << "->" << assm->getId() << ";" << endl;
        if(!childrenAreBase) {
            cassmQ->push((ComplexAssembly *)assm);
        } else {
            bassmQ->push((BaseAssembly *)assm);
        }
    }
}

void output::traverse(BaseAssembly *baseAssembly, queue<CompositePart *> *cpartQ, Set<DesignObj *> *visited, ofstream * graph) const {
    if(visited->contains(baseAssembly)){
        return;
    }
    visited->add(baseAssembly);
    *graph << baseAssembly->getId() << " [label=\"" << baseAssembly->getId() << "(" << baseAssembly->getPathLabel() << ")\"];" << endl;
    BagIterator<CompositePart *> iter = baseAssembly->getComponents()->getIter();
    while(iter.has_next()) {
        CompositePart * cp = iter.next();
        *graph << baseAssembly->getId() << "->" << cp->getId() << ";" << endl;
        cpartQ->push(cp);
    }
}

void output::traverse(CompositePart *component, queue<AtomicPart *> *apartQ, Set<DesignObj *> *visited, ofstream * graph) const {
    if (visited->contains(component)){
        return;
    }
    visited->add(component);
    *graph << component->getId() << " [label=\"" << component->getId() << "(" << component->getPathLabel() << ")\"];" << endl;
    AtomicPart *apart = component->getRootPart();
    *graph << component->getId() << "->" << apart->getId() << ";" << endl;
    apartQ->push(apart);
}

void output::traverse(AtomicPart *part, Set<DesignObj *> *visited, ofstream * graph) const {
    if(visited->contains(part)){
        return;
    }
    visited->add(part);
    *graph << part->getId() << " [label=\"" << part->getId() << "(" << part->getPathLabel() << ")\"];" << endl;
    Set<Connection *> *toConns = part->getToConnections();
    SetIterator<Connection *> iter = toConns->getIter();
    while(iter.has_next()) {
        Connection *conn = iter.next();
        *graph << part->getId() << "->" << conn->getDestination()->getId() << ";" << endl;
        traverse(conn->getDestination(), visited, graph);
    }
}
