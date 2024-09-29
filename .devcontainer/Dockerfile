# Using the base image with GCC
FROM gcc:14.2.0


# Installing dependencies for Google Test and CMake
RUN apt-get update && apt-get install -y \
    cmake \
    fish \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*


# Google Test compilation (libgtest-dev comes with source code only)
RUN cd /usr/src/gtest && cmake . && make && mv lib/*.a /usr/lib


# Setting the default working directory
WORKDIR /workspaces/ObjectOrientedProgrammingLab1

# Opening the port for debugging (optional)
# EXPOSE 8080