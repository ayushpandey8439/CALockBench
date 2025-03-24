echo >./output/CALock_Modifications.txt
for j in {0..7};do
for i in {0..4};do
./a.out 1000000 4 7 4 1 m true>>./output/CALock_Modifications.txt;
done
echo >>./output/CALock_Modifications.txt
done
