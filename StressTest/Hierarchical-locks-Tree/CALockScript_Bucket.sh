echo >./output/CALock_Bucket.txt
for j in {0..6};do
for i in {0..4};do
./a.out 1000000 4 7 4 $((2**$j)) m false>>./output/CALock_Bucket.txt;
done
echo >>./output/CALock_Bucket.txt
done
