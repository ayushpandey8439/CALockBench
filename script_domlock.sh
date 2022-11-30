echo >dom.txt
ITER=2
for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l dom -n 1 -w rw -d 12000| grep -i "throughput";done >>dom.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l dom -n 2 -w rw -d 12000| grep -i "throughput";done >>dom.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l dom -n 4 -w rw -d 12000| grep -i "throughput";done >>dom.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l dom -n 8 -w rw -d 12000| grep -i "throughput";done >>dom.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l dom -n 16 -w rw -d 12000| grep -i "throughput";done >>dom.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l dom -n 32 -w rw -d 12000| grep -i "throughput";done >>dom.txt

cut -d ' ' -f3 dom.txt >Results.txt
mv Results.txt dom.txt
