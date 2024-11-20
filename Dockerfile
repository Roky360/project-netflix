FROM ubuntu:latest
LABEL authors="Eden Kfir Avi"
LABEL version="0.1"

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    git \
    libgtest-dev

# Set the working directory
WORKDIR /app

# Copy the project files into the container
COPY . .

# Build the project
RUN mkdir build && cd build && \
    cmake .. && \
    make

# Set the default command to run the main executable
CMD ["./build/MyExecutable"]
