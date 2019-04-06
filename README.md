# CADG Centralized Aggregator and Dissemination Gateway

This is an open source solution for a FEMA IPAWS-like alert aggregator. [![Build Status](https://api.travis-ci.org/OS-WASABI/CADG.svg?branch=dev)](https://travis-ci.org/OS-WASABI/CADG)

## Table of Contents
* [Docker Compose](#docker-compose)
* [Install](#install)
* [Running](#running)
* [Credits](#credits)

## Docker-Compose
The preferred and simplest 
Launch the application with Docker compose from the [docker-cadg-compose](docker-cadg-compose) directory with
```
docker-compose up
```

## Install
On Ubuntu 18.04 LTS, run the following [env-setup.sh](docker-test-env/env-setup.sh) to install all needed dependencies.
```
sudo ./env-setup.sh
```
## Running
How to run individual modules.
### REST-Server
From the [rest-server](rest-server) directory
```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
./cadg-rest-server
```
### Testing
From the [test](test) directory
```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
./runTests
```

## Credits
Dev | Name
-------|------
![Vaniya Agrawal](/img/vaniya.png){:height="200px" width="200px"} | [Vaniya Agrawal](https://github.com/vsagrawal0)
![Ross Arcemont](/img/ross.png){:height="200px" width="200px"} | [Ross Arcemont](https://github.com/SilverStar07)
![Kristofer Hoadley](/img/kris.png){:height="200px" width="200px"} | [Kristofer Hoadley](https://github.com/kchoadley)
![Shawn Hulce](/img/shawn.jpg){:height="200px" width="200px"} | [Shawn Hulce](https://github.com/SHulce)
![Mike McCulley](/img/mike.png){:height="200px" width="200px"} | [Mike McCulley](https://github.com/ASUMike)