echo Benchmarking coarse-grain locking......
  j=1
  while [ $j -le $COUNT ]
  do
    echo "Thread count $(($j))"
              for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s $SIZE -l c -n $j -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/coarse$j.txt
              cut -d ' ' -f3 ./benchmarkResults/coarse$j.txt >./benchmarkResults/Results.txt
              mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse$j.csv
              rm ./benchmarkResults/coarse$j.txt
    j=$((j*2))
  done;

echo Benchmarking medium-grain locking......
  j=1
  while [ $j -le $COUNT ]
  do
    echo "Thread count $(($j))"
              for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s $SIZE -l m -n $j -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/medium$j.txt
              cut -d ' ' -f3 ./benchmarkResults/medium$j.txt >./benchmarkResults/Results.txt
              mv ./benchmarkResults/Results.txt ./benchmarkResults/medium$j.csv
              rm ./benchmarkResults/medium$j.txt
    j=$((j*2))
  done;


echo Benchmarking CALock......
  j=1
  while [ $j -le $COUNT ]
  do
    echo "Thread count $(($j))"
              for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s $SIZE -l ca -n $j -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/calock$j.txt
              cut -d ' ' -f3 ./benchmarkResults/calock$j.txt >./benchmarkResults/Results.txt
              mv ./benchmarkResults/Results.txt ./benchmarkResults/calock$j.csv
              rm ./benchmarkResults/calock$j.txt
    j=$((j*2))
  done;


echo Benchmarking DomLock......
  j=1
  while [ $j -le $COUNT ]
  do
    echo "Thread count $(($j))"
              for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s $SIZE -l dom -n $j -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/domlock$j.txt
              cut -d ' ' -f3 ./benchmarkResults/domlock$j.txt >./benchmarkResults/Results.txt
              mv ./benchmarkResults/Results.txt ./benchmarkResults/domlock$j.csv
              rm ./benchmarkResults/domlock$j.txt
    j=$((j*2))
  done;



echo Benchmarking MID......
  j=1
  while [ $j -le $COUNT ]
  do
    echo "Thread count $(($j))"
              for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./STMBench -s $SIZE -l mid -n $j -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/mid$j.txt
              cut -d ' ' -f3 ./benchmarkResults/mid$j.txt >./benchmarkResults/Results.txt
              mv ./benchmarkResults/Results.txt ./benchmarkResults/mid$j.csv
              rm ./benchmarkResults/mid$j.txt
    j=$((j*2))
  done;
