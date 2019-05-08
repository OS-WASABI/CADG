# Get the base test environment image from Docker Hub
FROM oswasabi/cadg-test-env:latest

# Set the working directory
WORKDIR "/usr/src/cadg"

# Copy the directories containing the source code to the Docker image under /usr/src
COPY "./rest-server/" "./rest-server/"
COPY "./test/" "./test/"
COPY "./soap/" "./soap/"

# You have to set an explicit error code, otherwise it goes undetected and you have to check the logs to see if there is an issue
RUN cppcheck --error-exitcode=1 \
    -i/rest-server/src/gSoapFiles \
    -irest-server/src/nanodbc \
    -irest-server/src/util \
    -isoap/pugixml-1.9 .

# Lint the files
RUN ./cpplint.py --headers=h --extensions=cpp --linelength=120 \
    /usr/src/cadg/test/*.cpp \
    /usr/src/cadg/test/*/*/*.cpp \
    /usr/src/cadg/rest-server/src/*.cpp \
    /usr/src/cadg/rest-server/src/controller/*.cpp \
    /usr/src/cadg/rest-server/src/services/*.cpp \
    /usr/src/cadg/soap/cmac-conversion/*.cpp \
    /usr/src/cadg/soap/xml-parsing/*.cpp

# Create build directory
WORKDIR "/usr/src/cadg/test"
RUN mkdir build
WORKDIR "/usr/src/cadg/test/build"

# Build and run tests
RUN cmake -G "Unix Makefiles" ..
RUN make
RUN ./runTests
