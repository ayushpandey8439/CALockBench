LOAD_TYPE=r
STRUCTURAL_MODIFICATIONS=true
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
pwd
. ./scripts/workloadRun.sh
pwd
#g++ plotter.cpp
#./a.out $COUNT