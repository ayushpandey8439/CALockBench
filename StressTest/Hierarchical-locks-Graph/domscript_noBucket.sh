echo >./output/DomLock_NoBucket.txt
for j in {0..7};do
for i in {0..4};do
./a.out 100000 8 5 $((2**$j)) 1 m >>./output/DomLock_NoBucket.txt;
done
echo >>./output/DomLock_NoBucket.txt
done