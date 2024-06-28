LOAD_TYPE=r
STRUCTURAL_MODIFICATIONS=false
rm -rf ./benchmarkResults/
mkdir ./benchmarkResults
pwd
. ./scripts/workloadRun.sh
pwd
python3 ./graphPlotGenerator.py $COUNT $ITERATIONS_PER_THREAD "ReadWithoutModifications"
mkdir -p ./benchmarkResultsBackup/ReadWithoutModifications  && mv ./benchmarkResults/* ./benchmarkResultsBackup/ReadWithoutModifications