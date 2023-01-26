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

    int Iterations = 5;
    output<<"ThreadCount, Domlock, CALock"<<"\n";

    for(int i=1;i<=9;i++)
    {
        string readPercentage = to_string((int)(i*10));
        ifstream casp_file("./benchmarkResults/caspinningReadPercent"+readPercentage+".txt");
        ifstream dom_file("./benchmarkResults/domReadPercent"+readPercentage+".txt");


        int cas=0,dom=0;
        int casc=0, domc=0;
        for(int j=0;j<Iterations;j++)
        {
            double caspval=0, domval=0;
            long double caspvali=0, domvali=0;
            long double caspvalm=0, domvalm=0;
            dom_file>>domval;

            casp_file>>caspval;
;
            cas+=caspval;dom+=domval;

            if(caspval>0) casc++;
            if(domval>0) domc++;
        }
        if(casc==0) casc++;
        if(domc==0) domc++;

        output<<readPercentage<<","<<dom/domc<<","<<cas/casc<<"\n";
        casp_file.close();
        dom_file.close();
    }

    output.close();

}
