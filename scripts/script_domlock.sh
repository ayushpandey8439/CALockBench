echo >./benchmarkResults/dom.txt
echo "Thread count 1"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 1 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS  -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 2"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 2 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS  -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 4"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 4 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS  -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 8"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 8 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 16"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 16 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 32"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 32 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 64"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 64 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 128"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 128 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt
echo "Thread count 256"
for((i=0;i< $ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s $SIZE -l dom -n 256 -w  $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d  $DURATION| grep -i "throughput";done >>./benchmarkResults/dom.txt

cut -d ' ' -f3 ./benchmarkResults/dom.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom.txt
