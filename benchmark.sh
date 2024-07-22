#!/bin/bash
COUNT=64
ITERATIONS_PER_THREAD=2
DURATION=2000
SIZE=b
set -e

echo Setting up python dependencies

python3 -m venv ./PythonEnv || exit 1
. ./PythonEnv/bin/activate || exit 1
python3 -m pip install matplotlib  || exit 1
python3 -m pip install pandas  || exit 1
python3 -m pip install numpy  || exit 1
python3 -m pip install seaborn || exit 1


echo Compiling Benchmark implementation on STMBench7......
rm -rf ./build
rm ./STMBench || true
mkdir ./build
cmake -S "./" -B "./build"
cmake --build "./build" --target STMBench -j6

rm -rf ./benchmarkCharts
mkdir ./benchmarkCharts
echo Running standard workload benchmarks
echo Step 1 of 6: Read Dominated load without modifications
. ./scripts/read.sh
echo Step 2 of 6: Read Dominated load with modifications
. ./scripts/readModifications.sh
echo Step 3 of 6: Write Dominated load without modifications
. ./scripts/write.sh
echo Step 4 of 6: Write Dominated load with modifications
. ./scripts/writeModifications.sh
echo Step 5 of 6: Balanced load without modifications
. ./scripts/balanced.sh
echo Step 6 of 6: Balanced load with modifications
. ./scripts/balancedModifications.sh