echo "Thread count 1"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l c -n 1 -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse1.txt
cut -d ' ' -f3 ./benchmarkResults/coarse1.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse1.txt

echo "Thread count 2"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l c -n 2 -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse2.txt
cut -d ' ' -f3 ./benchmarkResults/coarse2.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse2.txt

echo "Thread count 4"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l c -n 4 -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse4.txt
cut -d ' ' -f3 ./benchmarkResults/coarse4.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse4.txt\

echo "Thread count 8"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l c -n 8 -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse8.txt
cut -d ' ' -f3 ./benchmarkResults/coarse8.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse8.txt

echo "Thread count 16"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l c -n 16 -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse16.txt
cut -d ' ' -f3 ./benchmarkResults/coarse16.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse16.txt

echo "Thread count 32"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l c -n 32 -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse32.txt
cut -d ' ' -f3 ./benchmarkResults/coarse32.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse32.txt

#echo "Thread count 64"
#for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l c -n 64 -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/coarse64.txt
#cut -d ' ' -f3 ./benchmarkResults/coarse64.txt >./benchmarkResults/Results.txt
#mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse64.txt
