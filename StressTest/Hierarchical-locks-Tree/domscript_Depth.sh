echo >./output/Domlock_Depth.txt
for j in {20..31};do
for i in {0..4};do
./a.out  $((2**$j)) 1 5 1 1 s >>./output/Domlock_Depth.txt;
done
echo >>./output/Domlock_Depth.txt
done
