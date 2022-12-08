//
// Created by Ayush Pandey on 21/11/2022.
//
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

int main()
{
    ifstream c_file("./coarse.txt");
    ifstream m_file("./medium.txt");
    ifstream ca_file("./ca.txt");
    //ifstream dom_file("./dom.txt");
    //ifstream no_file("./nl.txt");
    //ifstream b_file("./stmbench7 baseline.c++/sb7_lock/baseline.txt");
    ofstream output("Results.txt");

    output<<"******************************************************\n";
    output<<"Each column represent throughput with particular locking technique\n";
    //output<<"Column 1: NoLock\n";
    output<<"Column 1: Coarse-grain lock\n";
    output<<"Column 2: Medium-grain lock\n";
    output<<"Column 3: CALock\n";
    //output<<"Column 4: Domlock\n";

    //output<<"Column 4: NoSync\n";
    output<<"X-axis of graph is number of threads from 1 to 32 in power of 2's and Y-axis is the throughput value\n\n";

    int Iterations = 5;

    for(int i=0;i<6;i++)
    {
        int c=0,m=0,ca=0,dom=0;
        for(int j=0;j<Iterations;j++)
        {
            double cval,mval,caval, domval;
            c_file>>cval;
            m_file>>mval;
            ca_file>>caval;
            //dom_file>>domval;
            c+=cval;m+=mval;ca+=caval;dom+=domval;
        }
        output<<c/Iterations<<"   "<<m/Iterations<<"   "<<ca/Iterations<<"\n";
    }

    c_file.close();
    m_file.close();
    ca_file.close();
    //dom_file.close();
    //b_file.close();
    output.close();

}
