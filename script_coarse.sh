echo >coarse.txt
ITER=20
for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l c -n 1 -w rw -d 200| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l c -n 2 -w rw -d 200| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l c -n 4 -w rw -d 200| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l c -n 8 -w rw -d 200| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l c -n 16 -w rw -d 200| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./target/STMBENCH -s b -l c -n 32 -w rw -d 200| grep -i "throughput";done >>coarse.txt

cut -d ' ' -f3 coarse.txt >Results.txt
mv Results.txt coarse.txt
