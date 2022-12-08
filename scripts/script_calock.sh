echo >./benchmarkResults/ca.txt
ITER=5
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 1 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 2 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 4 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 8 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
#
#for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 16 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt
#
#for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l ca -n 32 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/ca.txt

cut -d ' ' -f3 ./benchmarkResults/ca.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/ca.txt
