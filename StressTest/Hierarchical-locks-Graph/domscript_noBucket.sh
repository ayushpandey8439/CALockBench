echo >./output/DomLock_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000000 16 5 $((2**$j)) 1 s >>./output/DomLock_NoBucket.txt;
done
echo >>./output/DomLock_NoBucket.txt
done

echo >>./output/DomLock_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000000 16 5 $((2**$j)) 1 m >>./output/DomLock_NoBucket.txt;
done
echo >>./output/DomLock_NoBucket.txt
done

echo >>./output/DomLock_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000000 16 5 $((2**$j)) 1 l >>./output/DomLock_NoBucket.txt;
done
echo >>./output/DomLock_NoBucket.txt
done

