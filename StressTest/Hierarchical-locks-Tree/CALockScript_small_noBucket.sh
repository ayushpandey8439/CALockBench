echo >./output/CALock_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 2 7 $((2**$j)) 1 s >>./output/CALock_NoBucket.txt;
done
echo >>./output/CALock_NoBucket.txt
done

echo >>./output/CALock_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 2 7 $((2**$j)) 1 m >>./output/CALock_NoBucket.txt;
done
echo >>./output/CALock_NoBucket.txt
done

echo >>./output/CALock_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 2 7 $((2**$j)) 1 l >>./output/CALock_NoBucket.txt;
done
echo >>./output/CALock_NoBucket.txt
done

