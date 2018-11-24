# Get MySQL image from Docker Hub

FROM mysql

ENV MYSQL_ROOT_PASSWORD="example"

COPY *.sql .

RUN --default-authentication-plugin=mysql_native_password