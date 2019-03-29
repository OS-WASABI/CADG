### This creates the base image for the Build and Test Environment for CADG - SOAP Server

# Get the base Ubuntu image from Docker Hub
FROM ubuntu:18.04

# Add ubuntu toolchain repository
RUN apt-get -qq -d update
RUN apt-get install -qq -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get -qq -d update

# Install tools
RUN apt-get -qq -y install \
    cmake \
    cppcheck \
    g++-8 \
    libspdlog-dev \
    software-properties-common \
    unixodbc-dev \
    wget \
    doxygen

# Make g++ 8 the default g++ executable
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 90

# Google Fruit dependency injection, build install remove old files
RUN mkdir gfruit &&\
    cd gfruit &&\
    wget https://github.com/google/fruit/archive/v3.4.0.tar.gz &&\
    tar -xvzf v3.4.0.tar.gz &&\
    cd fruit-3.4.0 &&\
    cmake -DCMAKE_BUILD_TYPE=Release -DFRUIT_USES_BOOST=False . && make -j &&\
    make install &&\
    ldconfig

# Get gtest libraries, compile, move to lib folder, cleanup
RUN apt-get install libgtest-dev -y -qq &&\
    cd /usr/src/gtest &&\
    cmake CMakeLists.txt &&\
    make &&\
    cp *.a /usr/lib &&\
    cd .. &&\
    rm -R gtest
    
WORKDIR /usr/src/cadg

# Download cpplint.py and set the file permissions so that it is executable
RUN wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py &&\
    chmod +x cpplint.py

### Concludes base image
