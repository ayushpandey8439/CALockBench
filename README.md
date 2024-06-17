
CALock Benchmarks
===
This benchmark suite is based on STMBench7 and implements 4 different kinds of locks.
* Coarse lock
* Medium lock
* DomLock 
* CALock

All implementations can be found in the `Performance Tests/src` directory.

Directory structure
---

* `Performance Tests` - Contains the benchmarking scripts and the dockerfile to run the benchmark.
* `Performance Tests/src` - Contains the source code for the benchmark.
* `Performance Tests/benchmarkResults` - Contains the raw results of the benchmark.
* `Performance Tests/benchmarkCharts` - Contains the generated charts from the benchmark.
* `Performance Tests/benchmarkCharts<TIMESTAMP>` - Contains the generated charts from the benchmark. The timestamp is the time when the benchmark was run using the docker container. It is copied to the host machine.
* `Performance Tests/benchmark.sh` - The main script to run the benchmark without docker. The environment setup is not handled by this script. It is recommended to use the docker container to run the benchmark.
* `run_performance.sh` - The main script to run the benchmark using the docker container. It sets up the environment and runs the benchmark.
* `Performance Tests/scripts` - Scripts that are used for different benchmarking steps.

Sanity Testing
---
To ensure that the benchmark is set up properly, set the `COUNT` parameter in the `Performance Tests/benchmark.sh` script to 0. This will run the benchmark for 1 thread. The benchmark should finish in a few minutes. After that, there should be a few charts in the `Performance Tests/benchmarkCharts<TIMESTAMP>` directory. The charts should show the performance of the different locking algorithms for 1 thread.

Setting up the benchmark
---
The benchmark runs in a docker container. The setup of the environment and the runtime are handled by docker. To run the full suite, use the script `run_performance.sh`. The entire benchmark run takes between 4-6 hours to complete. It collects results for all the charts in the paper. 

The execution of specific benchmarks can be done by commenting out steps in the script `Performance Tests/benchmark.sh`.

Benchmark Parameters
---
The benchmark is executed for varying proportions of reads, writes and structural modification operations. The number of threads for the benchmark can be specified using the `COUNT` parameter in the `benchmark.sh` script. The default value is 64 threads. The test run begins with 1 thread and doubles the number of threads `COUNT` times. A `COUNT` value of 6 will run the benchmark for 1, 2, 4, 8, 16, 32 and 64 threads.

Benchmark Results
---
During every run, the benchmark raw results are stored in the `Performance Tests/benchmarkResults` directory. After processing, the image charts are generated in the `Performance Tests/benchmarkCharts` directory in the docker image. The charts are copied at the end of the whole benchmark to `Performance Tests/benchmarkCharts<TIMESTAMP>` on the host machine.


Running individual locking algorithms
---
The benchmark can be compiled via Cmake and results in an executable `sb7_lock`. The benchmark can be run with the following command line parameters:

--help (-?) - prints help
--readOnlyPercent (-p) <number> - set percent of read-only operations
--workloadType (-w) r|rw|w - set workload type
--structuralModifications (-m) true|false - enable/disable structural modifications
--threadNum (-n) <number> - set number of simultaneous threads
--size (-s) s|m|b - set size of data structure
--lockType (-l) n|c|m|ca|dom - set locking type


Example usage:

		./sb7_lock -s b -l m -n 12 -w rw -d 120000

It will run sb7_lock on a big data structure, using medium grained locking,
with twelve concurrent threads, running a read/write workload for two minutes
with long traversals turned on.