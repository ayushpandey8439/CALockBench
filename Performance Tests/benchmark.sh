echo Compiling Benchmark implementation on STMBench7......
make clean
make all
COUNT=3
rm -rf ./benchmarkCharts
mkdir ./benchmarkCharts
#echo Stage 1 of 2 : Running standard workload benchmarks
#echo Step 1 of 6: Read Dominated load without modifications
#. ./scripts/read.sh
#echo Step 2 of 6: Read Dominated load with modifications
#. ./scripts/readModifications.sh
#echo Step 3 of 6: Write Dominated load without modifications
#. ./scripts/write.sh
#echo Step 4 of 6: Write Dominated load with modifications
#. ./scripts/writeModifications.sh
#echo Step 5 of 6: Balanced load without modifications
#. ./scripts/balanced.sh
#echo Step 6 of 6: Balanced load with modifications
#. ./scripts/balancedModifications.sh

echo Stage 2 of 2: Running benchmark to find the intersection between domlock and CALock
echo Step 1 of 1: Running 10 to 90 percent reads
. ./scripts/VariableReadPercentage.sh