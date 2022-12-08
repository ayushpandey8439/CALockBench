echo >./benchmarkResults/coarse.txt
ITER=5
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l c -n 1 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/coarse.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l c -n 2 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/coarse.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l c -n 4 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/coarse.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l c -n 8 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/coarse.txt

#for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l c -n 16 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/coarse.txt
#
#for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l c -n 32 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/coarse.txt

cut -d ' ' -f3 ./benchmarkResults/coarse.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse.txt
