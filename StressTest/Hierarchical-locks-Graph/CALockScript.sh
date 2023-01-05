echo >./output/CALock.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000000 16 7 $((2**$j)) $((2**$i)) s >>./output/CALock.txt;
done
echo >>./output/CALock.txt
done

echo >>./output/CALock.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000000 16 7 $((2**$j)) $((2**$i)) m >>./output/CALock.txt;
done
echo >>./output/CALock.txt
done

echo >>./output/CALock.txt
for j in {1..8};do
for i in {0..4};do
./a.out 1000000 16 7 $((2**$j)) $((2**$i)) l >>./output/CALock.txt;
done
echo >>./output/CALock.txt
done

