for ((j=0;j<=$COUNT;j++))
do
  echo "Thread count $((2**$j))"

  for((i=0;i<2;i++));do ./sb7_lock -s b -l c -n $((2**$j)) -w $LOAD_TYPE -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/coarse$((2**$j)).txt
  cut -d ' ' -f3 ./benchmarkResults/coarse$((2**$j)).txt >./benchmarkResults/Results.txt
  mv ./benchmarkResults/Results.txt ./benchmarkResults/coarse$((2**$j)).txt
done;