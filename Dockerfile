FROM ubuntu:latest
RUN apt-get -y update && apt-get install make cmake g++ python3 python3-pip python3-venv -y

ARG src="./"

COPY ${src} /usr/CALockBench/
WORKDIR /usr/CALockBench/
RUN chmod +x benchmark.sh
RUN ./benchmark.sh