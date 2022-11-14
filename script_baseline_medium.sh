echo >medium.txt
ITER=20
for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l m -n 1 -w rw -d 200| grep -i "throughput";done >>medium.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l m -n 2 -w rw -d 200| grep -i "throughput";done >>medium.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l m -n 4 -w rw -d 200| grep -i "throughput";done >>medium.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l m -n 8 -w rw -d 200| grep -i "throughput";done >>medium.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l m -n 16 -w rw -d 200| grep -i "throughput";done >>medium.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l m -n 32 -w rw -d 200| grep -i "throughput";done >>medium.txt

cut -d ' ' -f3 medium.txt >Results.txt
mv Results.txt medium.txt
