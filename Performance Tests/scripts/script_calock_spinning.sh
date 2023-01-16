echo "Thread count 1"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 1 -w $LOAD_TYPE -b n -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/caspinning1.txt
cut -d ' ' -f3 ./benchmarkResults/caspinning1.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/caspinning1.txt

echo "Thread count 2"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 2 -w $LOAD_TYPE -b n -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/caspinning2.txt
cut -d ' ' -f3 ./benchmarkResults/caspinning2.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/caspinning2.txt

echo "Thread count 4"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 4 -w $LOAD_TYPE -b n -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/caspinning4.txt
cut -d ' ' -f3 ./benchmarkResults/caspinning4.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/caspinning4.txt\

echo "Thread count 8"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 8 -w $LOAD_TYPE -b n -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/caspinning8.txt
cut -d ' ' -f3 ./benchmarkResults/caspinning8.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/caspinning8.txt

echo "Thread count 16"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 16 -w $LOAD_TYPE -b n -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/caspinning16.txt
cut -d ' ' -f3 ./benchmarkResults/caspinning16.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/caspinning16.txt

echo "Thread count 32"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 32 -w $LOAD_TYPE -b n -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i -e "throughput" -e "idleness" -e "relabelling";done >>./benchmarkResults/caspinning32.txt
cut -d ' ' -f3 ./benchmarkResults/caspinning32.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/caspinning32.txt
#
#echo "Thread count 64"
#for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l ca -n 64 -w $LOAD_TYPE -b n -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/caspinning64.txt
#cut -d ' ' -f3 ./benchmarkResults/caspinning64.txt >./benchmarkResults/Results.txt
#mv ./benchmarkResults/Results.txt ./benchmarkResults/caspinning64.txt
