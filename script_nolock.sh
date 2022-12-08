echo >nl.txt
ITER=5
for((i=0;i<$ITER;i++));do ./STMBENCH -s b -l n -n 1 -w rw -d 6000| grep -i "throughput";done >>nl.txt

for((i=0;i<$ITER;i++));do ./STMBENCH -s b -l n -n 2 -w rw -d 6000| grep -i "throughput";done >>nl.txt

for((i=0;i<$ITER;i++));do ./STMBENCH -s b -l n -n 4 -w rw -d 6000| grep -i "throughput";done >>nl.txt

for((i=0;i<$ITER;i++));do ./STMBENCH -s b -l n -n 8 -w rw -d 6000| grep -i "throughput";done >>nl.txt

for((i=0;i<$ITER;i++));do ./STMBENCH -s b -l n -n 16 -w rw -d 6000| grep -i "throughput";done >>nl.txt

for((i=0;i<$ITER;i++));do ./STMBENCH -s b -l n -n 32 -w rw -d 6000| grep -i "throughput";done >>nl.txt

cut -d ' ' -f3 nl.txt >Results.txt
mv Results.txt nl.txt
