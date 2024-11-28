FROM gcc:latest
LABEL authors="Eden Kfir Avi"
LABEL version="0.2"

ARG CMAKE_VER=3.27.8
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
    cmake -DBUILD_TESTS=${BUILD_TESTS} .. && make

# Set the default command to run the main executable
CMD ["./build/project_netflix"]

# tree:
# app/
#   build/
#   src/
#   tests/
#   - CMakeLists.txt
#   CMakeLists.txt
# data/ data.db
#
