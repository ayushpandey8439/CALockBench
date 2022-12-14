echo >./benchmarkResults/ca.txt
echo "Thread count 1"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 1 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 2"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 2 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 4"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 4 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 8"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 8 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 16"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 16 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 32"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 32 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 64"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 64 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 128"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 128 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
echo "Thread count 256"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 256 -w rw -b $BLOCKING -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt

cut -d ' ' -f3 ./benchmarkResults/ca.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/ca.txt
