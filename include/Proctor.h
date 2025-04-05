/**
* @file Proctor.h
 * @brief Definition of the Proctor class.
 *
 * This file defines the Proctor class, which extends the User class and
 * includes additional attributes for role assignment.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#ifndef PROCTOR_H
#define PROCTOR_H

#include "User.h"  // Include base class User

class Proctor : public User {
private:
    // Role of the proctor
    // Pick from ONLY: "TA", "Course_Instructor" for now
    std::string role;

public:
    /**
     * @brief Constructs a Proctor object with the specified attributes.
     *
     * This constructor initializes a Proctor object by calling the base class User constructor
     * and setting the role of the proctor.
     *
     * @param ID The unique identifier of the proctor.
     * @param name The name of the proctor.
     * @param DOB The date of birth of the proctor.
     * @param pic_URL The URL of the proctor's profile picture.
     * @param role The role assigned to the proctor.
     */
    Proctor(int ID, const std::string &name, const std::string &DOB, const std::string &pic_URL, const std::string &role);

    /**
     * @brief Retrieves the role of the proctor.
     *
     * @return A string representing the role of the proctor.
     */
    std::string getRole() const;

    /**
     * @brief Sets the role of the proctor.
     *
     * @param role The new role to be assigned to the proctor.
     */
    void setRole(const std::string &role);
};

#endif // PROCTOR_H

