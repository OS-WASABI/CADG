cmake_minimum_required(VERSION 3.10)
project(soap_server)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog CONFIG REQUIRED)

add_executable(soap_server
        src/soap_server.cpp
        src/gSOAPFiles/soapC.cpp
        src/gSOAPFiles/CAPSoapHttp.nsmap
        src/gSOAPFiles/plugin/threads.cpp
        src/gSOAPFiles/soapCAPSoapHttpService.cpp
        src/gSOAPFiles/stdsoap2.cpp
        src/services/logger.cpp)

set(SERVICE_HEADERS "src/services")
set(SOAP_HEADERS "src/gSOAPFiles")
set(SOAP_PLUGIN_HEADERS "src/gSOAPFiles/plugin")

set(HEADER_PATHS ${SERVICE_HEADERS} ${SOAP_HEADERS} ${SOAP_PLUGIN_HEADERS})

set(SPDLOG_LIBRARY spdlog::spdlog)
set(PTHREAD_LIBRARY -lpthread)
set(LIBRARY_SEARCH_PATHS ${SPDLOG_LIBRARY} ${PTHREAD_LIBRARY})

include_directories(${HEADER_PATHS})
target_link_libraries(${PROJECT_NAME} ${LIBRARY_SEARCH_PATHS})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")