echo >./output/CALock_Depth.txt
for j in {15..22};do
for i in {0..4};do
./a.out  $((2**$j)) 1 7 1 1 s false >>./output/CALock_Depth.txt;
done
echo >>./output/CALock_Depth.txt
done
