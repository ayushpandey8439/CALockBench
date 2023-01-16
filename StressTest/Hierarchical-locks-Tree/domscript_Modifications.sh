echo >./output/Domlock_Modifications.txt
for j in {20..31};do
for i in {0..4};do
./a.out 1000000 4 5 4 1 m true>>./output/Domlock_Modifications.txt;
done
echo >>./output/Domlock_Modifications.txt
done
