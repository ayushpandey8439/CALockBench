echo >./output/CALock_NoBucket.txt
for j in {0..7};do
for i in {0..4};do
./a.out 100000 1 7 $((2**$j)) 1 m >>./output/CALock_NoBucket.txt;
done
echo >>./output/CALock_NoBucket.txt
done