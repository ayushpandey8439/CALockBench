echo >./output/DomLock_Bucket.txt
for j in {0..7};do
for i in {0..4};do
./a.out 1000000 8 5 8 $((2**$j)) m >>./output/DomLock_Bucket.txt;
done
echo >>./output/DomLock_Bucket.txt
done
