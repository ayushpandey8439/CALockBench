//
// Created by Ayush Pandey on 21/11/2022.
//
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

int main()
{
    ifstream c_file("./benchmarkResults/coarse.txt");
    ifstream m_file("./benchmarkResults/medium.txt");
    ifstream casp_file("./benchmarkResults/caspinning.txt");
    ifstream cab_file("./benchmarkResults/cablocking.txt");
    ifstream dom_file("./benchmarkResults/dom.txt");
    ofstream output("./benchmarkResults/Results.csv");

    output<<"******************************************************\n";
    output<<"Each column represent throughput with particular locking technique\n";
    //output<<"Column 1: NoLock\n";
    output<<"Column 1: Coarse-grain lock\n";
    output<<"Column 2: Medium-grain lock\n";
    output<<"Column 4: Domlock\n";
    output<<"Column 3: CALock Blocking\n";
    output<<"Column 3: CALock Spinning\n";

    //output<<"Column 4: NoSync\n";
    output<<"X-axis of graph is number of threads from 1 to 32 in power of 2's and Y-axis is the throughput value\n\n";

    int Iterations = 5;

    for(int i=0;i<7;i++)
    {
        int c=0,m=0,cab=0,cas=0,dom=0;
        for(int j=0;j<Iterations;j++)
        {
            double cval,mval,cabval,caspval, domval;
            c_file>>cval;
            m_file>>mval;
            cab_file>>cabval;
            dom_file>>domval;
            casp_file>>caspval;
            c+=cval;m+=mval;cab+=cabval;cas+=caspval;dom+=domval;
        }
        output<<c/Iterations<<","<<m/Iterations<<","<<dom/Iterations<<","<<cab/Iterations<<","<<cas/Iterations<<"\n";
    }

    c_file.close();
    m_file.close();
    casp_file.close();
    cab_file.close();
    dom_file.close();
    //b_file.close();
    output.close();

}
