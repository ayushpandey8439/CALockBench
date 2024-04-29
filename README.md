
CALock Benchmarks
===
Thie benchmark suite is based on STMBench7 and implements 4 different kinds of locks.
* Coarse lock
* Medium lock
* DomLock 
* CALock

All implementations can be found in the `Performance Tests/src` directory.


Setting up the benchmark
---
The benchmark runs in a docker container. The setup of the environment and the runtime are handled by docker. To run the full suite, use the script `run_performance.sh`. The entire benchmark run takes between 4-6 hours to complete. It collects results for all the charts in the paper. 

The execution of specific benchmarks can be done by commenting out steps is the script `Performance Tests/benchmark.sh`



Command line parameters for locking version are:
--help (-?) - prints help
--fileName (-f) <file_name> - sets options file name
--readOnlyPercent (-p) <number> - set percent of read-only operations
--workloadType (-w) r|rw|w - set workload type
--traversals (-t) true|false - enable/disable long traversals
--structuralModifications (-m) true|false - enable/disable structural modifications
--threadNum (-n) <number> - set number of simultaneous threads
--size (-s) s|m|b - set size of data structure
--lockType (-l) n|c|m|f - set locking type


Example usage:

		./sb7_lock -s b -l m -n 12 -w rw -d 120000

It will run sb7_lock on a big data structure, using medium grained locking,
with twelve concurrent threads, running a read/write workload for two minutes
with long traversals turned on.

Note: Fine grained locking is not implemented yet.
