echo >./output/DomLock_Bucket.txt
for j in {0..7};do
for i in {0..4};do
./a.out 1000000 8 5 4 $((2**$j)) m false>>./output/DomLock_Bucket.txt;
done
echo >>./output/DomLock_Bucket.txt
done
