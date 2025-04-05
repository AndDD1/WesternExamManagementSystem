/**
 *  @file User.cpp
 * @brief Implementation of the User class.
 *
 * This file defines the User class, which serves as a base class for different types
 * of users in the project. It includes attributes such as ID, name, date of birth,
 * and profile picture URL.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    int ID;                 // User's unique identifier
    std::string name;       // User's name
    std::string DOB;        // User's date of birth
    std::string pic_URL;    // User's picture URL

public:
   /**
   * @brief Constructs a User object with the specified attributes.
   *
   * This constructor initializes a User object with an ID, name, date of birth,
   * and profile picture URL.
   *
   * @param ID The unique identifier of the user.
   * @param name The name of the user.
   * @param DOB The date of birth of the user.
   * @param pic_URL The URL of the user's profile picture.
   */
    User(int ID, const std::string &name, const std::string &DOB, const std::string &pic_URL);

   /**
   * @brief Retrieves the user's ID.
   *
   * @return An integer representing the user's unique identifier.
   */
    int getID() const;

   /**
    * @brief Sets the user's ID.
    *
    * @param ID The new unique identifier for the user.
    */
    void setID(int ID);


   /**
   * @brief Retrieves the user's name.
   *
   * @return A string representing the user's name.
   */
    std::string getName() const;

   /**
     * @brief Sets the user's name.
     *
     * @param name The new name for the user.
     */
    void setName(const std::string &name);


    /**
     * @brief Retrieves the user's date of birth.
     *
     * @return A string representing the user's date of birth.
     */
    std::string getDOB() const;

    /**
     * @brief Sets the user's date of birth.
     *
     * @param DOB The new date of birth for the user.
     */
    void setDOB(const std::string &DOB);


    /**
     * @brief Retrieves the user's profile picture URL.
     *
     * @return A string representing the URL of the user's profile picture.
     */
    std::string getPicURL() const;

    /**
     * @brief Sets the user's profile picture URL.
     *
     * @param pic_URL The new URL for the user's profile picture.
     */
    void setPicURL(const std::string &pic_URL);
};

#endif // USER_H

