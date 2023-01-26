for ((j=9;j>0;j--))
do
  echo "Read Percentage "$((j*10))
  for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n $COUNT -p $((j*10)) -b n -m false -d $DURATION| grep -i "throughput";done >>./benchmarkResults/domReadPercent$((j*10)).txt
  cut -d ' ' -f3 ./benchmarkResults/domReadPercent$((j*10)).txt >./benchmarkResults/Results.txt
  mv ./benchmarkResults/Results.txt ./benchmarkResults/domReadPercent$((j*10)).txt
done;