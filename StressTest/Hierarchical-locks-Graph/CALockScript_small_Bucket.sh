echo >>./output/CALock_Bucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 16 7 8 $((2**$i)) m >>./output/CALock_Bucket.txt;
done
echo >>./output/CALock_Bucket.txt
done