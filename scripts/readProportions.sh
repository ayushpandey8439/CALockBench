for ((j=9;j>0;j--))
do
  echo "Read Percentage "$((j*10))
  for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s b -l ca -n $COUNT -p $((j*10)) -b n -m false -d $DURATION| grep -i "throughput";done >>./benchmarkResults/CAReadPercent$((j*10)).txt
  cut -d ' ' -f3 ./benchmarkResults/CAReadPercent$((j*10)).txt >./benchmarkResults/Results.txt
  mv ./benchmarkResults/Results.txt ./benchmarkResults/CAReadPercent$((j*10)).csv
  rm ./benchmarkResults/CAReadPercent$((j*10)).txt

  for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s b -l dom -n $COUNT -p $((j*10)) -b n -m false -d $DURATION| grep -i "throughput";done >>./benchmarkResults/DomReadPrecent$((j*10)).txt
  cut -d ' ' -f3 ./benchmarkResults/DomReadPrecent$((j*10)).txt >./benchmarkResults/Results.txt
  mv ./benchmarkResults/Results.txt ./benchmarkResults/DomReadPrecent$((j*10)).csv
  rm ./benchmarkResults/DomReadPrecent$((j*10)).txt

  for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s b -l mid -n $COUNT -p $((j*10)) -b n -m false -d $DURATION| grep -i "throughput";done >>./benchmarkResults/MidReadPrecent$((j*10)).txt
  cut -d ' ' -f3 ./benchmarkResults/MidReadPrecent$((j*10)).txt >./benchmarkResults/Results.txt
  mv ./benchmarkResults/Results.txt ./benchmarkResults/MidReadPrecent$((j*10)).csv
  rm ./benchmarkResults/MidReadPrecent$((j*10)).txt
done;