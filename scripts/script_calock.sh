echo >./benchmarkResults/ca.txt
ITER=5
echo "Thread count 1"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 1 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 2"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 2 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 4"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 4 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 8"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 8 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 16"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 16 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 32"
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 32 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt

cut -d ' ' -f3 ./benchmarkResults/ca.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/ca.txt
