echo "Thread count 1"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n 1 -w $LOAD_TYPE -b y -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/dom1.txt
cut -d ' ' -f3 ./benchmarkResults/dom1.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom1.txt

echo "Thread count 2"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n 2 -w $LOAD_TYPE -b y -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/dom2.txt
cut -d ' ' -f3 ./benchmarkResults/dom2.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom2.txt

echo "Thread count 4"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n 4 -w $LOAD_TYPE -b y -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/dom4.txt
cut -d ' ' -f3 ./benchmarkResults/dom4.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom4.txt\

echo "Thread count 8"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n 8 -w $LOAD_TYPE -b y -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/dom8.txt
cut -d ' ' -f3 ./benchmarkResults/dom8.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom8.txt

echo "Thread count 16"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n 16 -w $LOAD_TYPE -b y -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/dom16.txt
cut -d ' ' -f3 ./benchmarkResults/dom16.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom16.txt

echo "Thread count 32"
for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n 32 -w $LOAD_TYPE -b y -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/dom32.txt
cut -d ' ' -f3 ./benchmarkResults/dom32.txt >./benchmarkResults/Results.txt
mv ./benchmarkResults/Results.txt ./benchmarkResults/dom32.txt

#echo "Thread count 64"
#for((i=0;i<$ITERATIONS_PER_THREAD;i++));do ./sb7_lock -s b -l dom -n 64 -w $LOAD_TYPE -b y -m $STRUCTURAL_MODIFICATIONS -d $DURATION| grep -i "throughput";done >>./benchmarkResults/dom64.txt
#cut -d ' ' -f3 ./benchmarkResults/dom64.txt >./benchmarkResults/Results.txt
#mv ./benchmarkResults/Results.txt ./benchmarkResults/dom64.txt