echo >./output/Intention_Depth.txt
for j in {15..22};do
for i in {0..4};do
./a.out $((2**$j)) 1 4 1 1 m false >>./output/Intention_Depth.txt;
done
echo >>./output/Intention_Depth.txt
done
