FROM ubuntu:20.04

WORKDIR /app
RUN apt-get update && apt-get install -y 
RUN apt-get install -y \
    wget \
    git
RUN apt-get install -y build-essential
RUN apt-get install -y gcc
# RUN apt-get install -y gdb
    # cmake \
RUN apt-get install -y make
RUN apt-get install -y \
    ncurses-dev \
    libjansson-dev \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash devuser

CMD ["/bin/bash"]