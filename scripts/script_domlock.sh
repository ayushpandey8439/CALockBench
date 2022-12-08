echo >./benchmarkResults/dom.txt
ITER=5
for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l dom -n 1 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/dom.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l dom -n 2 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/dom.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l dom -n 4 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/dom.txt

for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l dom -n 8 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/dom.txt
#
#for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l dom -n 16 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/dom.txt
#
#for((i=0;i<$ITER;i++));do ./sb7_lock -s b -l dom -n 32 -w rw -d 2000| grep -i "throughput";done >>./benchmarkResults/dom.txt

cut -d ' ' -f3 ./benchmarkResults/dom.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom.txt
