echo >>./output/Intention_Bucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 16 4 8 $((2**$i)) m >>./output/Intention_Bucket.txt
done
echo >>./output/Intention_Bucket.txt
done