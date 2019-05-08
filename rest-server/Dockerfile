# Get the base test environment image from Docker Hub
FROM oswasabi/cadg-test-env:latest

# Set the working directory
WORKDIR "/usr/src/cadg-rest-server"

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY "./src/" "./src/"
COPY CMakeLists.txt .

ENV DB_ADMIN_NAME=${DB_ADMIN_NAME}
ENV DB_ADMIN_TABLE=${DB_ADMIN_TABLE}
ENV DB_ALERT_TABLE=${DB_ALERT_TABLE}
ENV DB_CADG_NAME=${DB_CADG_NAME}
ENV DB_DISSEMINATOR_TABLE=${DB_DISSEMINATOR_TABLE}
ENV DB_PASSWORD=${DB_PASSWORD}
ENV DB_PORT=${DB_PORT}
ENV DB_SERVER=${DB_SERVER}
ENV DB_UID=${DB_UID}

RUN mkdir build
WORKDIR "/usr/src/cadg-rest-server/build"

RUN cmake -G "Unix Makefiles" ..
RUN make

CMD ["./cadg-rest-server"]
