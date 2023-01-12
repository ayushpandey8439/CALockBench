#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

int main()
{
	//********************************************************************************
	//Plots for tree data structure
	//********************************************************************************

	fstream DomFile("./Hierarchical-locks-Tree/output/DomLock_Depth.txt");
	fstream ILFile("./Hierarchical-locks-Tree/output/Intention_Depth.txt");
    fstream CAFile("./Hierarchical-locks-Tree/output/CALock_Depth.txt");
    ofstream TreeOutput;
    TreeOutput.open("./dataForPlots/TreeDepth.csv");


    //iterate for different number of nodes to be locked from 1 to 128
    TreeOutput<<"Domlock,Intention Lock,CALock\n";
    for(int j=0;j<12;j++)
    {

        //iterate for different distribution from 1 to 16
        double DomAvg = 0,ILAvg = 0, CAAvg=0;
        for(int k=0;k<5;k++)
        {
            double DomVal,ILVal, CAVal;
            DomFile>>DomVal;
            ILFile>>ILVal;
            CAFile>>CAVal;

            DomAvg = DomAvg + DomVal;
            ILAvg = ILAvg + ILVal;
            CAAvg += CAVal;

        }
        TreeOutput<<(double)DomAvg/5<<","<<(double)ILAvg/5<<","<<(double)CAAvg/5<<"\n";
    }

    TreeOutput<<endl;
    TreeOutput.close();

	DomFile.close();
	ILFile.close();
    CAFile.close();
}
