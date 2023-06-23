FROM ubuntu:18.04

WORKDIR /app
RUN apt-get update 
RUN apt-get install -y \
    wget \
    build-essential \
    gcc \
    git \
    gdb \
    cmake \
    make \
    ncurses-dev \
    && rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]