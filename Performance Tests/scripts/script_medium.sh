echo "Thread count 1"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l m -n 1 -w $LOAD_TYPE  -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/medium1.txt
cut -d ' ' -f3 ./benchmarkResults/medium1.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/medium1.txt

echo "Thread count 2"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l m -n 2 -w $LOAD_TYPE  -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/medium2.txt
cut -d ' ' -f3 ./benchmarkResults/medium2.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/medium2.txt

echo "Thread count 4"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l m -n 4 -w $LOAD_TYPE  -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/medium4.txt
cut -d ' ' -f3 ./benchmarkResults/medium4.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/medium4.txt

echo "Thread count 8"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l m -n 8 -w $LOAD_TYPE  -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/medium8.txt
cut -d ' ' -f3 ./benchmarkResults/medium8.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/medium8.txt

echo "Thread count 16"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l m -n 16 -w $LOAD_TYPE  -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/medium16.txt
cut -d ' ' -f3 ./benchmarkResults/medium16.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/medium16.txt

echo "Thread count 32"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l m -n 32 -w $LOAD_TYPE  -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/medium32.txt
cut -d ' ' -f3 ./benchmarkResults/medium32.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/medium32.txt

#echo "Thread count 64"
#for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l m -n 64 -w $LOAD_TYPE  -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/medium64.txt
#cut -d ' ' -f3 ./benchmarkResults/medium64.txt >./benchmarkResults/Results.txt
#mv ./benchmarkResults/Results.txt ./benchmarkResults/medium64.txt
