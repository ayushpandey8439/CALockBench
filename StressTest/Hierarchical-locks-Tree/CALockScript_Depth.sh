echo >./output/CALock_Depth.txt
for j in {20..31};do
for i in {0..4};do
./a.out  $((2**$j)) 1 7 1 1 s >>./output/CALock_Depth.txt;
done
echo >>./output/CALock_Depth.txt
done
