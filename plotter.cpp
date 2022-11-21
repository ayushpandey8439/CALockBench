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
    //ifstream b_file("./stmbench7 baseline.c++/sb7_lock/baseline.txt");
    ofstream output("Figure_4.txt");

    output<<"******************************************************\n";
    output<<"Each column represent throughput with particular locking technique\n";
    output<<"Column 1: Coarse-grain lock\n";
    output<<"Column 2: Medium-grain lock\n";
    output<<"Column 3: CALock\n";
    //output<<"Column 4: NoSync\n";
    output<<"X-axis of graph is number of threads from 1 to 32 in power of 2's and Y-axis is the throughput value\n\n";


    for(int i=0;i<6;i++)
    {
        int c=0,m=0,ca=0;
        for(int j=0;j<20;j++)
        {
            double cval,mval,caval;
            c_file>>cval;
            m_file>>mval;
            ca_file>>caval;
            //b_file>>bval;
            c+=cval;m+=mval;ca+=caval;

        }
        output<<c/20<<" "<<m/20<<" "<<ca/20<<"\n";
    }

    c_file.close();
    m_file.close();
    ca_file.close();
    //b_file.close();
    output.close();

}
