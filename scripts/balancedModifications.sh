LOAD_TYPE=rw
STRUCTURAL_MODIFICATIONS=true
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
pwd
. ./scripts/workloadRun.sh
pwd
python3 ./graphPlotGenerator.py $COUNT $ITERATIONS_PER_THREAD "BalancedWithModifications"
mkdir  -p ./benchmarkResultsBackup/BalancedWithModifications && mv ./benchmarkResults ./benchmarkResultsBackup/BalancedWithModifications