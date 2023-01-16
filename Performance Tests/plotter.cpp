//
// Created by Ayush Pandey on 21/11/2022.
//
#include<iostream>
#include<fstream>
#include<math.h>
#include "vector"
using namespace std;

int main()
{
    ofstream output("./benchmarkResults/Results.csv");
    ofstream outputi("./benchmarkResults/IdlenessResults.csv");
    ofstream outputm("./benchmarkResults/ModificationResults.csv");
    int Iterations = 5;
    output<<"ThreadCount, Coarse, Medium, Domlock, CALock"<<"\n";
    outputi<<"ThreadCount,Domlock, CALock"<<"\n";
    outputm<<"ThreadCount,Domlock, CALock"<<"\n";
    for(int i=0;i<6;i++)
    {
        string threadCount = to_string((int)pow(2,i));
        ifstream c_file("./benchmarkResults/coarse"+threadCount+".txt");
        ifstream m_file("./benchmarkResults/medium"+threadCount+".txt");
        ifstream casp_file("./benchmarkResults/caspinning"+threadCount+".txt");
        ifstream dom_file("./benchmarkResults/dom"+threadCount+".txt");

        vector<double> c,m,cas,dom;
        vector<double> casi,domi;
        vector<double> casm,domm;
        for(int j=0;j<Iterations;j++)
        {
            double cval=0,mval=0,caspval=0, domval=0;
            double caspvali=0, domvali=0;
            double caspvalm=0, domvalm=0;
            c_file>>cval;
            m_file>>mval;
            dom_file>>domval;
            dom_file>>domvalm;
            dom_file>>domvali;
            casp_file>>caspval;
            casp_file>>caspvalm;
            casp_file>>caspvali;

            c.push_back(cval);
            m.push_back(mval);
            dom.push_back(domval);
            cas.push_back(caspval);

            casm.push_back(caspvalm);
            domm.push_back(domvalm);

            casi.push_back(caspvali);
            domi.push_back(domvali);
        }

        nth_element(c.begin(),c.begin()+2, c.end());
        nth_element(m.begin(),m.begin()+2, m.end());
        nth_element(dom.begin(),dom.begin()+2, dom.end());
        nth_element(cas.begin(),cas.begin()+2, cas.end());

        nth_element(domi.begin(),domi.begin()+2, domi.end());
        nth_element(casi.begin(),casi.begin()+2, casi.end());

        nth_element(domm.begin(),domm.begin()+2, domm.end());
        nth_element(casm.begin(),casm.begin()+2, casm.end());

        output<<threadCount<<","<<c[2]<<","<<m[2]<<","<<dom[2]<<","<<cas[2]<<"\n";
        outputi<<threadCount<<","<<domi[2]<<","<<casi[2]<<"\n";
        outputm<<threadCount<<","<<domm[2]<<","<<casm[2]<<"\n";
        c_file.close();
        m_file.close();
        casp_file.close();
        dom_file.close();
    }


    //b_file.close();
    output.close();
    outputi.close();
    outputm.close();
}
