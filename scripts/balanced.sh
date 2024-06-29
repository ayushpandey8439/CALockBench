LOAD_TYPE=rw
STRUCTURAL_MODIFICATIONS=false
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
pwd
. ./scripts/workloadRun.sh
pwd
python3 ./graphPlotGenerator.py $COUNT $ITERATIONS_PER_THREAD "BalancedWithoutModifications"
mkdir -p ./benchmarkResultsBackup/BalancedWithoutModifications && mv ./benchmarkResults/* ./benchmarkResultsBackup/BalancedWithoutModifications