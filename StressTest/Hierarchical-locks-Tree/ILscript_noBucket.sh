echo >./output/Intention_NoBucket.txt
for j in {0..7};do
for i in {0..4};do
./a.out 1000000 1 4 $((2**$j)) 1 m >>./output/Intention_NoBucket.txt
done
echo >>./output/Intention_NoBucket.txt
done