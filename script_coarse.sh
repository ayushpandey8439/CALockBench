echo >coarse.txt
ITER=2
for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l c -n 1 -w rw -d 2000| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l c -n 2 -w rw -d 2000| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l c -n 4 -w rw -d 2000| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l c -n 8 -w rw -d 2000| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l c -n 16 -w rw -d 2000| grep -i "throughput";done >>coarse.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l c -n 32 -w rw -d 2000| grep -i "throughput";done >>coarse.txt

cut -d ' ' -f3 coarse.txt >Results.txt
mv Results.txt coarse.txt
