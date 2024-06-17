LOAD_TYPE=rw
READ_ONLY_PERCENT=100
DURATION=2000
SIZE=b
STRUCTURAL_MODIFICATIONS=false
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
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
./a.out $COUNT

python3 ./graphImageGenerator.py 'BalancedWithoutModifications' $COUNT
