#include<iostream>
#include<fstream>
#include<math.h>
#include "vector"
#include <algorithm>
using namespace std;

int main()
{
	//********************************************************************************
	//Plots for tree data structure
	//********************************************************************************

	fstream DomFile("./Hierarchical-locks-Tree/output/DomLock_Bucket.txt");
	fstream ILFile("./Hierarchical-locks-Tree/output/Intention_Bucket.txt");
    fstream CAFile("./Hierarchical-locks-Tree/output/CALock_Bucket.txt");
    ofstream TreeOutput("./dataForPlots/Skewness.csv");
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
}
