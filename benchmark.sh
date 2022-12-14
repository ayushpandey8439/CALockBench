echo Compiling Benchmark implementation on STMBench7......
make clean
make all
BLOCKING=n
LOAD_TYPE=
READ_ONLY_PERCENT=100
DURATION=2000
SIZE=b
ITERATIONS_PER_THREAD=5
STRUCTURAL_MODIFICATIONS=false
echo Benchmarking coarse-grain locking......
. ./scripts/script_coarse.sh
echo Benchmarking medium-grain locking......
. ./scripts/script_medium.sh
echo Benchmarking CALock......
. ./scripts/script_calock.sh
echo Benchmarking Domlock......
. ./scripts/script_domlock.sh
pwd
g++ plotter.cpp
./a.out
