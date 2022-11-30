echo Compiling Benchmark implementation on STMBench7......
cmake --build /Users/pandey/work/CALockBenchmarks/build --target STMBENCH -j 6

echo Benchmarking coarse-grain locking......
./script_coarse.sh
echo Benchmarking medium-grain locking......
./script_medium.sh
echo Benchmarking CALock......
./script_calock.sh
echo Benchmarking Domlock......
./script_domlock.sh
pwd
g++ Plotter.cpp
./a.out
