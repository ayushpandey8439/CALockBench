LOAD_TYPE=r
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
#echo Benchmarking CALock......
#. ./scripts/script_calock_spinning.sh
#echo Benchmarking Domlock......
#. ./scripts/script_domlock.sh
pwd
g++ plotter.cpp
./a.out $COUNT

<<<<<<< HEAD
cp ./benchmarkResults/Results.csv ./benchmarkCharts/ReadWithoutModifications.csv
cp ./benchmarkResults/IdlenessResults.csv ./benchmarkCharts/ReadWithoutModificationsIdleness.csv
cp ./benchmarkResults/ModificationResults.csv ./benchmarkCharts/ReadWithoutModificationsModifications.csv

python3 ./graphImageGenerator.py 'ReadWithoutModifications'
=======
python3 ./graphImageGenerator.py 'ReadWithoutModifications' $COUNT
>>>>>>> blockingImplementation
