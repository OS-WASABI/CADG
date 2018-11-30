// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <gtest/gtest.h>
#include "controller.hpp"
using cadg_rest::Controller;

TEST(ControllerTest, ExtractsQueries) {
    auto queries = Controller::Queries("");
    EXPECT_EQ(queries.size(), 0);

    queries = Controller::Queries("name=kris");
    EXPECT_EQ(queries.size(), 1);
    EXPECT_EQ(queries["name"], "kris");

    queries = Controller::Queries("name=kris&id=1");
    EXPECT_EQ(queries.size(), 2);
    EXPECT_EQ(queries["name"], "kris");
    EXPECT_EQ(queries["id"], "1");
}