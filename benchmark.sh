COUNT=2
ITERATIONS_PER_THREAD=3
DURATION=2000
SIZE=b

echo Setting up python dependencies

python3 -m venv ./PythonEnv || exit 1
source ./PythonEnv/bin/activate || exit 1
python3 -m pip install matplotlib  || exit 1
python3 -m pip install pandas  || exit 1
python3 -m pip install numpy  || exit 1


echo Compiling Benchmark implementation on STMBench7......
cmake -S "./" -B "./build"
cmake --build "./build" --target STMBench -j6

rm -rf ./benchmarkCharts
mkdir ./benchmarkCharts
echo Stage 1 of 3 : Running standard workload benchmarks
echo Step 1 of 6: Read Dominated load without modifications
. ./scripts/read.sh
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
#
#echo Stage 2 of 3: Running benchmark to find the intersection between domlock and CALock
#echo Step 1 of 1: Running 10 to 90 percent reads
#. ./scripts/VariableReadPercentage.sh
#
#echo Stage 3 of 3: Running benchmark to find number of vertices locked per vertex type
#. ./scripts/script_lockProportions.sh