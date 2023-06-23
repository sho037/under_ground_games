FROM ubuntu:leatest

WORKDIR /app
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    git \
    gdb \
    cmake \
    make \
    ncurses-dev \
    && rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]