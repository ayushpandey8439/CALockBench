echo >>./output/DomLock_Bucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000000 16 5 8 $((2**$i)) m >>./output/DomLock_Bucket.txt;
done
echo >>./output/DomLock_Bucket.txt
done