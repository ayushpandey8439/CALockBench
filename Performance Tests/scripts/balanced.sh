LOAD_TYPE=rw
DURATION=2000
SIZE=b
ITERATIONS_PER_THREAD=5
STRUCTURAL_MODIFICATIONS=false
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
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
./a.out $COUNT

<<<<<<< HEAD
cp ./benchmarkResults/Results.csv ./benchmarkCharts/BalancedWithoutModifications.csv
cp ./benchmarkResults/IdlenessResults.csv ./benchmarkCharts/BalancedWithoutModificationsIdleness.csv
cp ./benchmarkResults/ModificationResults.csv ./benchmarkCharts/BalancedWithoutModificationsModifications.csv


python3 ./graphImageGenerator.py 'BalancedWithoutModifications'
=======
python3 ./graphImageGenerator.py 'BalancedWithoutModifications' $COUNT
>>>>>>> blockingImplementation
