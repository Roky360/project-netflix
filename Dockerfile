FROM gcc:latest
LABEL authors="Eden Kfir Avi"
LABEL version="0.3"

ARG CMAKE_VER=3.25.1
ARG BUILD_TESTS=OFF

# Install dependencies
RUN apt-get update && apt-get install -y cmake

# Set the working directory
WORKDIR /app

# Copy the project files and tests
COPY CMakeLists.txt .
COPY src/ src/
COPY tests/ tests/

# Build the project
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_VER=${CMAKE_VER} -DBUILD_TESTS=${BUILD_TESTS} .. && make

# Set the default command to run the main executable
CMD ["./build/project_netflix"]
