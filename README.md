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
<img src="./img/vaniya.png" width="200" height="200"> | [Vaniya Agrawal](https://github.com/vsagrawal0)
<img src="./img/ross.png" width="200" height="200"> | [Ross Arcemont](https://github.com/SilverStar07)
<img src="./img/kris.png" width="200" height="200"> | [Kristofer Hoadley](https://github.com/kchoadley)
<img src="./img/shawn.jpg" width="200" height="200"> | [Shawn Hulce](https://github.com/SHulce)
<img src="./img/mike.png" width="200" height="200"> | [Mike McCulley](https://github.com/ASUMike)