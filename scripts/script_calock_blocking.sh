echo >./benchmarkResults/cablocking.txt
echo "Thread count 1"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 1 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 2"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 2 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 4"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 4 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 8"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 8 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 16"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 16 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 32"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 32 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 64"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 64 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 128"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 128 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt
echo "Thread count 256"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 256 -w $LOAD_TYPE -b y -d 2000| grep -i "throughput";done >>./benchmarkResults/cablocking.txt

cut -d ' ' -f3 ./benchmarkResults/cablocking.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/cablocking.txt
