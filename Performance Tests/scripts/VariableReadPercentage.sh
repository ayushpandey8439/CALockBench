DURATION=2000
SIZE=b
ITERATIONS_PER_THREAD=5
STRUCTURAL_MODIFICATIONS=false
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
echo Benchmarking CALock......
. ./scripts/script_calock_32Threads.sh
echo Benchmarking Domlock......
. ./scripts/script_domlock_32Threads.sh
pwd
g++ ReadPercentageplotter.cpp
./a.out

python3 ./VariableReadImageGenerator.py