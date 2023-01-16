echo >./output/Intention_Modifications.txt
for j in {0..7};do
for i in {0..4};do
./a.out 1000000 4 4 4 1 m true>>./output/Intention_Modifications.txt
done
echo >>./output/Intention_Modifications.txt
done
