LOAD_TYPE=w
READ_ONLY_PERCENT=100
DURATION=2000
SIZE=b
ITERATIONS_PER_THREAD=5
STRUCTURAL_MODIFICATIONS=false
rm -rf ./benchmarkResults
mkdir benchmarkResults
echo Benchmarking coarse-grain locking......
. ./scripts/script_coarse.sh
echo Benchmarking medium-grain locking......
. ./scripts/script_medium.sh
echo Benchmarking CALock Spinning......
. ./scripts/script_calock_spinning.sh
echo Benchmarking Domlock......
. ./scripts/script_domlock.sh
pwd
g++ plotter.cpp
./a.out

cp ./benchmarkResults/Results.csv ./benchmarkCharts/WriteWithoutModifications.csv


python3 ./graphImageGenerator.py './benchmarkResults/Results.csv' 'WriteWithoutModifications'