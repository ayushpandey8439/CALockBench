#include<iostream>
#include<fstream>
#include<math.h>
#include "vector"
using namespace std;

int main()
{
	//********************************************************************************
	//Plots for tree data structure
	//********************************************************************************

	fstream DomFile("./Hierarchical-locks-Tree/output/DomLock_NoBucket.txt");
	fstream ILFile("./Hierarchical-locks-Tree/output/Intention_NoBucket.txt");
    fstream CAFile("./Hierarchical-locks-Tree/output/CALock_NoBucket.txt");
    ofstream TreeOutput;
    TreeOutput.open("./dataForPlots/TreeCS.csv");


    //iterate for different number of nodes to be locked from 1 to 128
    TreeOutput<<"Domlock,Intention Lock,CALock\n";
    for(int j=0;j<8;j++)
    {

        //iterate for different distribution from 1 to 16
        vector<double> DomAvg,ILAvg, CAAvg;
        for(int k=0;k<5;k++)
        {
            double DomVal,ILVal, CAVal;
            DomFile>>DomVal;
            ILFile>>ILVal;
            CAFile>>CAVal;

            DomAvg.push_back(DomVal);
            ILAvg.push_back(ILVal);
            CAAvg.push_back(CAVal);

        }
        nth_element(DomAvg.begin(),DomAvg.begin()+2, DomAvg.end());
        nth_element(ILAvg.begin(),ILAvg.begin()+2, ILAvg.end());
        nth_element(CAAvg.begin(),CAAvg.begin()+2, CAAvg.end());
        TreeOutput<<DomAvg[2]<<","<<ILAvg[2]<<","<<CAAvg[2]<<"\n";
    }

    TreeOutput<<endl;
    TreeOutput.close();

	DomFile.close();
	ILFile.close();
    CAFile.close();

	//********************************************************************************
	//Plots for directed graphs
	//********************************************************************************
	
	fstream DomFileGraph("./Hierarchical-locks-Graph/output/DomLock_NoBucket.txt");
	fstream ILFileGraph("./Hierarchical-locks-Graph/output/Intention_NoBucket.txt");
    fstream CAFileGraph("./Hierarchical-locks-Graph/output/CALock_NoBucket.txt");
    ofstream GraphOutput;

        GraphOutput.open("./dataForPlots/GraphCS.csv");
//		GraphOutput<<endl;
    //iterate for different number of nodes to be locked from 1 to 128
    GraphOutput<<"Domlock,Intention Lock,CALock\n";
    for(int j=0;j<6;j++)
    {
        //iterate for different distribution from 1 to 16
        double DomAvg = 0,ILAvg = 0, CAAvg=0;
        for(int k=0;k<5;k++)
        {
            double DomVal,ILVal, CAVal;
            DomFileGraph>>DomVal;
            ILFileGraph>>ILVal;
            CAFileGraph>>CAVal;
            DomAvg = DomAvg + DomVal;
            ILAvg = ILAvg + ILVal;
            CAAvg +=CAVal;

        }
        GraphOutput<<(double)DomAvg/5<<","<<(double)ILAvg/5<<","<<(double)CAAvg/5<<"\n";
    }

    GraphOutput<<endl;
    GraphOutput.close();
	DomFileGraph.close();
	ILFileGraph.close();
    CAFileGraph.close();
}
