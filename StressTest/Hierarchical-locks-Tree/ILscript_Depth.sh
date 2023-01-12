echo >./output/Intention_Depth.txt
for j in {20..31};do
for i in {0..4};do
./a.out $((2**$j)) 1 4 1 1 m>>./output/Intention_Depth.txt;
done
echo >>./output/Intention_Depth.txt
done
