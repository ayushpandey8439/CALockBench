echo >./output/Intention_Bucket.txt
for j in {0..7};do
for i in {0..4};do
./a.out 1000000 8 4 4 $((2**$j)) m false>>./output/Intention_Bucket.txt
done
echo >>./output/Intention_Bucket.txt
done
