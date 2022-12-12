echo >./benchmarkResults/medium.txt
ITER=5
echo "Thread count 1"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l m -n 1 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/medium.txt
echo "Thread count 2"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l m -n 2 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/medium.txt
echo "Thread count 4"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l m -n 4 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/medium.txt
echo "Thread count 8"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l m -n 8 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/medium.txt
echo "Thread count 16"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l m -n 16 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/medium.txt
echo "Thread count 32"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l m -n 32 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/medium.txt

cut -d ' ' -f3 ./benchmarkResults/medium.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/medium.txt
