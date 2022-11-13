FROM --platform=linux/amd64 ubuntu:22.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential cmake doxygen python-is-python3
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y clang

COPY . /repo
WORKDIR /repo
RUN make -j8
RUN make install PREFIX=/install
RUN clang++ mayhem/fuzz_truncate_utf8.cpp -fsanitize=fuzzer,address -I /install/include/opencc/ -o /fuzz

FROM ubuntu:22.04 as package
COPY --from=builder /install /install
COPY --from=builder /fuzz /fuzz_truncate_utf8
ENV LD_LIBRARY_PATH=/install/lib

