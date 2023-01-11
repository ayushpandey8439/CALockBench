echo >./output/CALock_Bucket.txt
for j in {0..7};do
for i in {0..4};do
./a.out 1000 4 7 4 $((2**$i)) m >>./output/CALock_Bucket.txt;
done
echo >>./output/CALock_Bucket.txt
done