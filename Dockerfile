FROM ubuntu:latest
RUN apt-get -y update && apt-get install make cmake g++ python3 python3-pip -y
RUN pip3 install matplotlib numpy pandas

ARG src="Performance Tests/"

COPY ${src} /usr/CALockBench/
WORKDIR /usr/CALockBench/
RUN cmake -S "/usr/CALockBench/" -B "/usr/CALockBench/build"
RUN cmake --build "/usr/CALockBench/build" --target sb7_lock
#RUN cp /usr/CALockBench/build/sb7_lock ../
RUN chmod +x benchmark.sh
RUN ls -l ./scripts
CMD bash ./benchmark.sh
