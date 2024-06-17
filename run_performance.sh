#!/bin/bash

docker compose up --build

docker cp LockBenchmark:/usr/CALockBench/benchmarkCharts ./benchmarkCharts$(date -d "today" +"%Y%m%d%H%M")

