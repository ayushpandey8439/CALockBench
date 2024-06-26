LOAD_TYPE=r
DURATION=2000
SIZE=b
ITERATIONS_PER_THREAD=5
STRUCTURAL_MODIFICATIONS=true
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults/
echo Benchmarking coarse-grain locking......
. ./scripts/script_coarse.sh
echo Benchmarking medium-grain locking......
. ./scripts/script_medium.sh
#echo Benchmarking CALock Spinning......
#. ./scripts/script_calock_spinning.sh
#echo Benchmarking Domlock......
#. ./scripts/script_domlock.sh
pwd
g++ plotter.cpp
<<<<<<< HEAD
./a.out  $COUNT

cp ./benchmarkResults/Results.csv ./benchmarkCharts/ReadWithModifications.csv
cp ./benchmarkResults/IdlenessResults.csv ./benchmarkCharts/ReadWithModificationsIdleness.csv
cp ./benchmarkResults/ModificationResults.csv ./benchmarkCharts/ReadWithModificationsModifications.csv

python3 ./graphImageGenerator.py  'ReadWithModifications'
=======
./a.out $COUNT

python3 ./graphImageGenerator.py 'ReadWithModifications' $COUNT
>>>>>>> blockingImplementation
