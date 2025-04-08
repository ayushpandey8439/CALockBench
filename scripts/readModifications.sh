LOAD_TYPE=r
STRUCTURAL_MODIFICATIONS=true
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
pwd
. ./scripts/workloadRun.sh
pwd
python3 ./graphPlotGenerator.py $COUNT $ITERATIONS_PER_THREAD "ReadWithModifications"
mkdir -p  ./benchmarkResultsBackup/ReadWithModifications && mv ./benchmarkResults/* ./benchmarkResultsBackup/ReadWithModifications