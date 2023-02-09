//
// Created by Ayush Pandey on 21/11/2022.
//
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

int main(int argc, char** argv)
{
    ofstream output("./benchmarkResults/Results.csv");
    ofstream outputi("./benchmarkResults/IdlenessResults.csv");
    ofstream outputm("./benchmarkResults/RelabellingResults.csv");

    int Iterations = 5;
    output<<"ThreadCount, Coarse, Medium, Domlock, CALock"<<"\n";
    outputi<<"ThreadCount,Domlock, CALock"<<"\n";
    outputm<<"ThreadCount,Domlock, CALock"<<"\n";

    int count = atoi(argv[1]);
    for(int i=0;i<=count;i++)
    {
        string threadCount = to_string((int)pow(2,i));
        ifstream c_file("./benchmarkResults/coarse"+threadCount+".txt");
        ifstream m_file("./benchmarkResults/medium"+threadCount+".txt");
        ifstream casp_file("./benchmarkResults/caspinning"+threadCount+".txt");
        ifstream dom_file("./benchmarkResults/dom"+threadCount+".txt");


        int c=0,m=0,cas=0,dom=0;
        long int casi=0,domi=0;
        long int casm=0,domm=0;
        int cc=0, mc=0,casc=0, domc=0;
        for(int j=0;j<Iterations;j++)
        {
            double cval=0,mval=0,caspval=0, domval=0;
            long double caspvali=0, domvali=0;
            long double caspvalm=0, domvalm=0;
            c_file>>cval;
            m_file>>mval;
            dom_file>>domval;
            dom_file>>domvalm;
            dom_file>>domvali;
            casp_file>>caspval;
            casp_file>>caspvalm;
            casp_file>>caspvali;
            c+=cval;m+=mval;cas+=caspval;dom+=domval;
            casi+=caspvali; domi+=domvali;
            casm+=caspvalm; domm+=domvalm;

            if(cval>0) cc++;
            if(mval>0) mc++;
            if(caspval>0) casc++;
            if(domval>0) domc++;
        }

        if(cc==0) cc++;
        if(mc==0) mc++;
        if(casc==0) casc++;
        if(domc==0) domc++;

        output<<threadCount<<","<<c/cc<<","<<m/mc<<","<<dom/domc<<","<<cas/casc<<"\n";
        outputi<<threadCount<<","<<domi/domc<<","<<casi/casc<<"\n";
        outputm<<threadCount<<","<<domm/domc<<","<<casm/casc<<"\n";

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
