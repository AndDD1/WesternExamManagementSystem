/**
 * @file Proctor.cpp
 * @brief Implementation of the Proctor class.
 *
 * This file implements the Proctor class, which extends the User class and
 * includes additional attributes for role assignment.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#include "Proctor.h"

// Constructor
Proctor::Proctor(int ID, const std::string &name, const std::string &DOB, const std::string &pic_URL, const std::string &role)
    : User(ID, name, DOB, pic_URL), role(role) {}

// Getter for Role
std::string Proctor::getRole() const {
    return role;
}

// Setter for Role
void Proctor::setRole(const std::string &role) {
    this->role = role;
}
