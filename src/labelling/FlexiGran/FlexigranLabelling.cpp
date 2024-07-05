//
// Created by Ayush Pandey on 04/07/2024.
//

#include "FlexigranLabelling.h"

#include <climits>

#include "../../struct/connection.h"

long int flexiCounter = 0;

int sb7::FlexigranLabelling::run(int tid) const
{
    dataHolder->getModule()->getDesignRoot()->m_levelFromRoot = 0; // Setting root's level
    int retval = traverse(dataHolder->getModule()->getDesignRoot());
    cout << "\nRoot pre-post:  " << dataHolder->getModule()->getDesignRoot()->m_pre_number << " and " << dataHolder->
        getModule()->getDesignRoot()->m_post_number << endl;

    return retval;
}

int sb7::FlexigranLabelling::traverse(ComplexAssembly* cassm) const
{
    int partsVisited = 0;
    if (cassm->m_pre_number == 0)
        cassm->m_pre_number = ++flexiCounter;
    else ++flexiCounter;

    Set<Assembly*>* subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly*> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();
    int myLevel = cassm->m_levelFromRoot;
    int pre = INT_MAX, post = 0;

    // think about transforming this into a nicer oo design
    while (iter.has_next())
    {
        Assembly* assm = iter.next();
        assm->m_levelFromRoot = myLevel + 1; // Setting child node's level
        if (!childrenAreBase)
        {
            partsVisited += traverse((ComplexAssembly*)assm);
        }
        else
        {
            partsVisited += traverse((BaseAssembly*)assm);
        }
        //
        // if(assm->m_pre_number < pre)
        //   pre = assm->m_pre_number;
        // if(assm->m_post_number > post)
        //   post = assm->m_post_number;
    }

    // cassm->m_pre_number = pre;
    cassm->m_post_number = ++flexiCounter;


    return partsVisited;
}

int sb7::FlexigranLabelling::traverse(BaseAssembly* bassm) const
{
    int partsVisited = 0;
    if (bassm->m_pre_number == 0)
        bassm->m_pre_number = ++flexiCounter;
    else ++flexiCounter;

    BagIterator<CompositePart*> iter = bassm->getComponents()->getIter();
    int myLevel = bassm->m_levelFromRoot;
    while (iter.has_next())
    {
        CompositePart* cpart = iter.next();
        cpart->m_levelFromRoot = myLevel + 1;
        partsVisited += traverse(cpart);
    }
    bassm->m_post_number = ++flexiCounter;
    return partsVisited;
}

int sb7::FlexigranLabelling::traverse(CompositePart* cpart) const
{
    //  if(cpart -> m_pre_number == 0)
    //  cpart -> m_pre_number = flexiCounter++;
    //  else flexiCounter++;
    if (cpart->m_pre_number == 0)
        cpart->m_pre_number = ++flexiCounter;
    else ++flexiCounter;

    // if (cpart->m_pre_number != cpart->m_post_number)
    // {
    //     cout << cpart->getId() << ": (" << cpart->m_pre_number << ", " << cpart->m_post_number << ")" << endl;
    // }

    AtomicPart* rootPart = cpart->getRootPart();
    Set<AtomicPart*> visitedPartSet;
    cpart->m_post_number = ++flexiCounter;
    rootPart->m_levelFromRoot = cpart->m_levelFromRoot + 1;
    // int myLevel = cpart->m_levelFromRoot;
    int retval = traverse(rootPart, visitedPartSet);


    //cout << "Composite part id : " << cpart->getId() << "-------" << endl;
    // Assign intervals to all connected atomic parts
    // SetIterator<AtomicPart*> iter = visitedPartSet.getIter();
    // while (iter.has_next())
    // {
    //     AtomicPart* ap = iter.next();
    //     ap->m_pre_number = cpart->m_pre_number;
    //     ap->m_post_number = cpart->m_post_number;
    //     ap->m_levelFromRoot = myLevel + 1;
    //     //cout << ap->getId() << endl;
    // }
    //cout << "-------" << endl;
    return retval;
}


int sb7::FlexigranLabelling::traverse(AtomicPart* apart,
                                      Set<AtomicPart*>& visitedPartSet) const
{
    int ret;

    if (apart == NULL)
    {
        ret = 0;
    }
    else if (visitedPartSet.contains(apart))
    {
        ret = 0;
    }
    else
    {
        apart->m_pre_number = ++flexiCounter;
        apart->m_levelFromRoot = apart->getPartOf()->m_levelFromRoot + 1;
        ret = performOperationOnAtomicPart(apart, visitedPartSet);
        visitedPartSet.add(apart);

        // visit all connected parts
        Set<Connection*>* toConns = apart->getToConnections();
        SetIterator<Connection*> iter = toConns->getIter();

        while (iter.has_next())
        {
            Connection* conn = iter.next();
            ret += traverse(conn->getDestination(), visitedPartSet);
        }
    }
    return ret;
}

int sb7::FlexigranLabelling::performOperationOnAtomicPart(AtomicPart* apart,
                                                          Set<AtomicPart*>& visitedPartSet) const
{
    apart->nullOperation();
    return 1;
}
