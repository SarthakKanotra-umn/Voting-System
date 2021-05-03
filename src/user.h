/**
 * @file user.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef USER_H_
#define USER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "election.h"

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief User class implementation
 *
 * The User class contains the runElection() method which
 * runs the elections taking in a String and a file.
 *
 */
 
class User {
  public:
 /**
 * @brief Constructor that takes in a string for the type
 */
    User(string type);
 /**
 * @brief runElection() method runs the election taking in a String and a file
 */
    void runElection(string user, FILE file);

  private:
 /**
 * @brief String that contains the User's type
 */
    string typeUser;

};

#endif  // USER_H_
