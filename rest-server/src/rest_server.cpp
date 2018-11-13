// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "another_controller.hpp"
#include "example_controller.hpp"
#include "user_controller.hpp"
#include "data_access_interface.hpp"
#include "data_access_object.hpp"
using aoi_rest::DataAccessInterface;
using aoi_rest::DataAccessObject;
using aoi_rest::AnotherController;
using aoi_rest::ExampleController;
using aoi_rest::UserController;

int main(int argc, const char * argv[]) {
    std::cout << "Starting aoi rest server" << std::endl;
    DataAccessInterface* user_dao = &DataAccessObject::Instance();
    AnotherController another_controller;
    ExampleController example_controller;
    UserController user_controller(*user_dao);
    std::string server_address;
    if (argc > 2)
        server_address.append(argv[2]);
    else
        server_address.append("http://host_auto_ip4");
    if (argc > 1)
        server_address.append(argv[1]);
    else
        server_address.append(":8080");
    server_address.append("/v1/aoi/api");
    another_controller.endpoint(server_address + "/another");
    example_controller.endpoint(server_address + "/example");
    user_controller.endpoint(server_address + "/users");
    try {
        another_controller.Accept().wait();
        example_controller.Accept().wait();
        user_controller.Accept().wait();
        std::cout << "Listening for requests at: "
                << another_controller.endpoint() << std::endl
                << "Listening for requests at: "
                << example_controller.endpoint() << std::endl
                << "Listening for requests at: "
                << user_controller.endpoint() << std::endl;
        std::cout << "Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
        another_controller.Shutdown().wait();
        example_controller.Shutdown().wait();
        user_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        std::cerr << "There was an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
