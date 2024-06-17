echo $((2**$COUNT))

for ((j=9;j>0;j--))
do
  echo "Read Percentage "$((j*10))
  for((i=0;i<2;i++));do ./sb7_lock -s b -l dom -n $((2**$COUNT)) -p $((j*10)) -b n -m false -d $DURATION| grep -i "throughput";done >>./benchmarkResults/domReadPercent$((j*10)).txt
  cut -d ' ' -f3 ./benchmarkResults/domReadPercent$((j*10)).txt >./benchmarkResults/Results.txt
  mv ./benchmarkResults/Results.txt ./benchmarkResults/domReadPercent$((j*10)).txt
done;
