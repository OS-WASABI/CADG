### CADG React build container
# Used in the docker-compose for building the React app used by the apache server.
# Note, uses a shared volume with the apache server

# Get base node image from Docker Hub
FROM node:latest

COPY . /cadg-ui
WORKDIR /cadg-ui

RUN npm install
RUN npm run build
