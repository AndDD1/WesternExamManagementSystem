/**
*  @file User.cpp
 * @brief Implementation of the User class.
 *
 * This file implements the User class, which serves as a base class for different types
 * of users in the project. It includes attributes such as ID, name, date of birth,
 * and profile picture URL.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */


#include "User.h"

// Constructor
User::User(int ID, const std::string &name, const std::string &DOB, const std::string &pic_URL)
    : ID(ID), name(name), DOB(DOB), pic_URL(pic_URL) {}

// Getter for ID
int User::getID() const {
    return ID;
}

// Setter for ID
void User::setID(int ID) {
    this->ID = ID;
}

// Getter for Name
std::string User::getName() const {
    return name;
}

// Setter for Name
void User::setName(const std::string &name) {
    this->name = name;
}

// Getter for DOB
std::string User::getDOB() const {
    return DOB;
}

// Setter for DOB
void User::setDOB(const std::string &DOB) {
    this->DOB = DOB;
}

// Getter for Picture URL
std::string User::getPicURL() const {
    return pic_URL;
}

// Setter for Picture URL
void User::setPicURL(const std::string &pic_URL) {
    this->pic_URL = pic_URL;
}
