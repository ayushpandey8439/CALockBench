echo >ca.txt
ITER=2
for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l ca -n 1 -w rw -d 12000| grep -i "throughput";done >>ca.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l ca -n 2 -w rw -d 12000| grep -i "throughput";done >>ca.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l ca -n 4 -w rw -d 12000| grep -i "throughput";done >>ca.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l ca -n 8 -w rw -d 12000| grep -i "throughput";done >>ca.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l ca -n 16 -w rw -d 12000| grep -i "throughput";done >>ca.txt

for((i=0;i<$ITER;i++));do ./build/STMBENCH -s b -l ca -n 32 -w rw -d 12000| grep -i "throughput";done >>ca.txt

cut -d ' ' -f3 ca.txt >Results.txt
mv Results.txt ca.txt
