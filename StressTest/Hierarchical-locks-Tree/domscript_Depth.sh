echo >./output/Domlock_Depth.txt
for j in {15..22};do
for i in {0..4};do
./a.out  $((2**$j)) 1 5 1 1 s false>>./output/Domlock_Depth.txt;
done
echo >>./output/Domlock_Depth.txt
done
