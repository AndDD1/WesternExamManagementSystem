/**
 * @file UserTest.cpp
 * @brief Unit tests for the User class.
 *
 * This file contains Google Test cases for the User class, ensuring
 * proper initialization and correct behavior of getter and setter methods
 * for ID, name, date of birth, and profile picture URL.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */


#include <gtest/gtest.h>
#include "User.h"

// Test fixture for User class
class UserTest : public ::testing::Test {
protected:
    // Setup: Create a User object before each test
    User user{1, "John Doe", "2000-01-01", "https://example.com/pic.jpg"};
};

// Test case: Constructor initializes correctly
TEST_F(UserTest, ConstructorInitialization) {
    EXPECT_EQ(user.getID(), 1);
    EXPECT_EQ(user.getName(), "John Doe");
    EXPECT_EQ(user.getDOB(), "2000-01-01");
    EXPECT_EQ(user.getPicURL(), "https://example.com/pic.jpg");
}

// Test case: ID getter and setter
TEST_F(UserTest, IDGetterSetter) {
    user.setID(2);
    EXPECT_EQ(user.getID(), 2);
}

// Test case: Name getter and setter
TEST_F(UserTest, NameGetterSetter) {
    user.setName("Alice Smith");
    EXPECT_EQ(user.getName(), "Alice Smith");
}

// Test case: DOB getter and setter
TEST_F(UserTest, DOBGetterSetter) {
    user.setDOB("1995-06-15");
    EXPECT_EQ(user.getDOB(), "1995-06-15");
}

// Test case: Picture URL getter and setter
TEST_F(UserTest, PicURLGetterSetter) {
    user.setPicURL("https://example.com/newpic.jpg");
    EXPECT_EQ(user.getPicURL(), "https://example.com/newpic.jpg");
}


