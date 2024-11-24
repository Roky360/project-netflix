FROM gcc:latest
LABEL authors="Eden Kfir Avi"
LABEL version="0.1"

ARG CMAKE_VER=3.27.8
ARG BUILD_TESTS=OFF

# Install dependencies
# Update and install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    libssl-dev \
    && apt-get clean

# Install CMake 3.27.8
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VER}/cmake-${CMAKE_VER}-linux-x86_64.sh \
    && chmod +x cmake-3.27.8-linux-x86_64.sh \
    && ./cmake-3.27.8-linux-x86_64.sh --skip-license --prefix=/usr/local \
    && rm cmake-3.27.8-linux-x86_64.sh
#RUN apt-get update && apt-get install -y \
#    cmake \
#    make
#    g++ \
#    git \
#    libgtest-dev

# Set the working directory
WORKDIR /app

# Copy the project files into the container
COPY . .

# Build the project
RUN mkdir build && cd build && \
    cmake -DCMAKE_VER=${CMAKE_VER} -DBUILD_TESTS=${BUILD_TESTS} .. && \
    cmake --build .

# Set the default command to run the main executable
CMD ["./build/project_netflix"]
