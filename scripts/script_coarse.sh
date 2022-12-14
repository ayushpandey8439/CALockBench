echo >./benchmarkResults/coarse.txt
echo "Thread count 1"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l c -n 1 -w $LOAD_TYPE -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse.txt

echo "Thread count 2"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l c -n 2 -w $LOAD_TYPE -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse.txt

echo "Thread count 4"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l c -n 4 -w $LOAD_TYPE -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse.txt

echo "Thread count 8"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l c -n 8 -w $LOAD_TYPE -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse.txt

echo "Thread count 16"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l c -n 16 -w $LOAD_TYPE -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse.txt

echo "Thread count 32"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l c -n 32 -w $LOAD_TYPE -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse.txt

cut -d ' ' -f3 ./benchmarkResults/coarse.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse.txt
