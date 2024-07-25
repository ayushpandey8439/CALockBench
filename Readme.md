CALock Benchmark
================

This is a benchmark suite for CALock. It uses STMBench7 and compares CALock against Intention locks, DomLock, MID and Flexigran.
The benchmark is written in C++ and can be run standalone if the system is compatible with CXX 23 otherwise, a docker image is provided.

## Running the benchmark
To run the standalone benchmark, the script `benchmark.sh` can be used. It sets up the python virtual environment, the variables used across 
the different scripts and executes the different workloads. 

To run the docker image, `docker compose up --build` can be used to set up the image and run the benchmark. The container is called `LockBenchmark`
and can be used to retrieve the raw data results via `docekr cp -r LockBenchmark:/usr/CALockBench/benchmarkResultsBkup ./results`. 
The generated charts can be retrieved via `docker cp -r LockBenchmark:/usr/CALockBench/benchmarkCharts ./charts`.

If there is a need to generate charts using raw data collected earlier, the script `allChartGenerator.sh` can be used.


Individual performance charts for completion time, metadata size etc. contain precompiled results can can be generated via their respective python scripts.

## Configuring the benchmark
In order to not run the benchmark with its default configuration, several parameters can be changed. 
`benchmark.sh` contains the following parameters that can be changed:

* `COUNT`: Maximum number of threads. The benchmark starts with 1 thread and doubles the number of threads until `COUNT` is reached.
* `ITERATIONS_PER_THREAD`: The number of times the same workload is executed. This should be kept higher than 1 so that average performance can be measured.
* `DURATION`: The duration of the benchmark in milliseconds. This is used to calculate the throughput.
* `SIZE`: Size of the STMBench7 hierarchy to use. 

Individual workloads are defined in their own scripts and are executed in steps. 
The `benchmark.sh` script can be modified to run only specific workloads or to run them in a different order.


For every workload, all lock implementations are executed. To modify this and run only specific lock implementations, the `scripts/workloadRun.sh` script can be changed. Note however that chart generation might fail if not 
all lock implementations are executed or their raw data is available. 

## Dependencies
The benchmark requires the following dependencies to be installed:
* Python 3
* Seaborn
* Matplotlib
* Pandas
* CXX 23
* Docker
* Docker compose
