#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

int main()
{
	//********************************************************************************
	//Plots for tree data structure
	//********************************************************************************

	fstream DomFile("./Hierarchical-locks-Tree/output/DomLock.txt");
	fstream ILFile("./Hierarchical-locks-Tree/output/Intention.txt");
    fstream CAFile("./Hierarchical-locks-Tree/output/CALock.txt");
    ofstream TreeOutput;
	ofstream Distribution("Figure_6_a-f.csv");

//	TreeOutput<<"First column represents execution time(in second) with DomLock and  \n Second column represent execution time(in second) for Intention locks \n Third column represents execution time(in second) for CAlocks\n";
//
//	TreeOutput<<"X-axis is the number of locked nodes from 2 to 256 in power of 2's\n";
//	TreeOutput<<"Y-axis is the execution time in second\n";
//
//	Distribution<<"X-axis is the value of distribution and Y-axis is execution time in second\n";
	//Iterate three times to compute values for small medium and large critical section
	for(int i=0;i<3;i++)
	{
//		TreeOutput<<"Plots for ";
//
		if(i==0)
           TreeOutput.open("./dataForPlots/TreeSmallCS.csv");
		if(i==1)
            TreeOutput.open("./dataForPlots/TreeMediumCS.csv");
		if(i==2)
            TreeOutput.open("./dataForPlots/TreeLargeCS.csv");

//		TreeOutput<<endl;
		//iterate for different number of nodes to be locked from 1 to 128
        TreeOutput<<"Domlock,Intention Lock,CALock\n";
		for(int j=0;j<8;j++)
		{	

//			if(i==1)
//			{
//				Distribution<<"Plot for distribution with "<<pow(2,j+1)<<" nodes"<<endl<<"DomLock -- Intention Locks--CALock\n";
//			}
			//iterate for different distribution from 1 to 16
			double DomAvg = 0,ILAvg = 0, CAAvg=0;
			for(int k=0;k<5;k++)
			{
				double DomVal,ILVal, CAVal;
				DomFile>>DomVal;
				ILFile>>ILVal;
                CAFile>>CAVal;
				if(i==1)
				{
					Distribution<<DomVal<<","<<ILVal<<","<<CAVal<<"\n";
				}

				DomAvg = DomAvg + DomVal;
				ILAvg = ILAvg + ILVal;
                CAAvg += CAVal;

			}	
			TreeOutput<<(double)DomAvg/5<<","<<(double)ILAvg/5<<","<<(double)CAAvg/5<<"\n";
			if(i==1)
			Distribution<<endl;
		}

		TreeOutput<<endl;
        TreeOutput.close();
	}

	DomFile.close();
	ILFile.close();
    CAFile.close();

	//********************************************************************************
	//Plots for directed graphs
	//********************************************************************************
	
	fstream DomFileGraph("./Hierarchical-locks-Graph/output/DomLock.txt");
	fstream ILFileGraph("./Hierarchical-locks-Graph/output/Intention.txt");
    fstream CAFileGraph("./Hierarchical-locks-Graph/output/CALock.txt");
    ofstream GraphOutput;

//	GraphOutput<<"First column represent execution time with DomLock and \n Second column represent execution time for Intention locks\n";
//
//	GraphOutput<<"X-axis is the number of locked nodes from 2 to 64 in power of 2's\n";
//	GraphOutput<<"Y-axis is the execution time in second\n";
	//Iterate 3 times to compute values for small medium and large critical section
	for(int i=0;i<3;i++)
	{	
//		GraphOutput<<"Plots for ";
//
		if(i==0)
            GraphOutput.open("./dataForPlots/GraphSmallCS.csv");
		if(i==1)
            GraphOutput.open("./dataForPlots/GraphMediumCS.csv");
		if(i==2)
            GraphOutput.open("./dataForPlots/GraphLargeCS.csv");
//
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
	}

	DomFileGraph.close();
	ILFileGraph.close();
    CAFileGraph.close();
}
