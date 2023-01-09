echo >./output/Intention_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 2 4 $((2**$j)) 1 s >>./output/Intention_NoBucket.txt
done
echo >>./output/Intention_NoBucket.txt
done

echo >>./output/Intention_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 2 4 $((2**$j)) 1 m >>./output/Intention_NoBucket.txt
done
echo >>./output/Intention_NoBucket.txt
done

echo >>./output/Intention_NoBucket.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000 2 4 $((2**$j)) 1 l >>./output/Intention_NoBucket.txt
done
echo >>./output/Intention_NoBucket.txt
done

