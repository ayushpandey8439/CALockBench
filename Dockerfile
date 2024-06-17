FROM ubuntu:latest
RUN apt-get -y update && apt-get install make cmake g++ python3 python3-pip python3-matplotlib python3-numpy python3-pandas -y

ARG src="Performance Tests/"

COPY ${src} /usr/CALockBench/
WORKDIR /usr/CALockBench/
RUN cmake -S "/usr/CALockBench/" -B "/usr/CALockBench/build"
RUN cmake --build "/usr/CALockBench/build" --target sb7_lock -j6
#RUN cp /usr/CALockBench/build/sb7_lock ../
RUN chmod +x benchmark.sh
RUN ls -l ./scripts
CMD bash ./benchmark.sh
