/// Tests the User Controller Class
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    user_controller_test.cpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#include <gtest/gtest.h>
#include "user_controller.hpp"
#include "mock_logger.hpp"
#include "mock_data_access.hpp"

using cadg_rest::UserController;
using cadg_rest::MockDataAccess;
using cadg_rest::MockLogger;


class UserControllerTest : public ::testing::Test {
    UserController user_controller(MockLogger logger, MockDataAccess dao);
};

TEST_F(UserControllerTest, InitializesHandlers) { }

TEST_F(UserControllerTest, HandlesGet) { }

TEST_F(UserControllerTest, HandlesPost) { }

TEST_F(UserControllerTest, HandlesPut) { }

TEST_F(UserControllerTest, HandlesDelete) { }

TEST_F(UserControllerTest, ReturnsUserById) { }

TEST_F(UserControllerTest, ReturnsUserByName) { }

TEST_F(UserControllerTest, ParsesUserId) {
    // std::string path = "http://localhost:8080/users/1";
    // ASSERT_EQ(user_controller.ParseUserId(path), "1");
}
