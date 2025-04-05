/**
 * @file ProctorTest.cpp
 * @brief Unit tests for the Proctor class.
 *
 * This file contains Google Test cases for the Proctor class, ensuring
 * proper initialization, inheritance from User, and correct behavior
 * of getter and setter methods for ID, name, date of birth, picture URL,
 * and role attributes.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */


#include <gtest/gtest.h>
#include "Proctor.h"

// Test fixture for Proctor class
class ProctorTest : public ::testing::Test {
protected:
    // Setup: Create a Proctor object before each test
    Proctor proctor{101, "Dr. Smith", "1985-04-23", "https://example.com/proctor.jpg", "TA"};
};

// Test case: Constructor initializes correctly
TEST_F(ProctorTest, ConstructorInitialization) {
    EXPECT_EQ(proctor.getID(), 101);
    EXPECT_EQ(proctor.getName(), "Dr. Smith");
    EXPECT_EQ(proctor.getDOB(), "1985-04-23");
    EXPECT_EQ(proctor.getPicURL(), "https://example.com/proctor.jpg");
    EXPECT_EQ(proctor.getRole(), "TA");
}

// Test case: ID getter and setter (inherited)
TEST_F(ProctorTest, IDGetterSetter) {
    proctor.setID(202);
    EXPECT_EQ(proctor.getID(), 202);
}

// Test case: Name getter and setter (inherited)
TEST_F(ProctorTest, NameGetterSetter) {
    proctor.setName("Prof. Johnson");
    EXPECT_EQ(proctor.getName(), "Prof. Johnson");
}

// Test case: DOB getter and setter (inherited)
TEST_F(ProctorTest, DOBGetterSetter) {
    proctor.setDOB("1975-08-15");
    EXPECT_EQ(proctor.getDOB(), "1975-08-15");
}

// Test case: Picture URL getter and setter (inherited)
TEST_F(ProctorTest, PicURLGetterSetter) {
    proctor.setPicURL("https://example.com/new_proctor.jpg");
    EXPECT_EQ(proctor.getPicURL(), "https://example.com/new_proctor.jpg");
}

// Test case: Role getter and setter
TEST_F(ProctorTest, RoleGetterSetter) {
    proctor.setRole("Course_Instructor");
    EXPECT_EQ(proctor.getRole(), "Course_Instructor");
}


