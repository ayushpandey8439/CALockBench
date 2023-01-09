echo >>./output/CALock_Bucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 10000 16 7 4 $((2**$i)) m >>./output/CALock_Bucket.txt;
done
echo >>./output/CALock_Bucket.txt
done