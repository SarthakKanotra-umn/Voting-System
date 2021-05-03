/**
 * @file election_official.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef ELECTION_OFFICIAL_H_
#define ELECTION_OFFICIAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "user.h"
#include "ir.h"
#include "opl.h"
#include "PO.h"

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Election Official class implementation
 *
 * This class contains a loadFile() command that loads the file
 * for the election and returns the number of ballots.
 *
 */

class ElectionOfficial {
  public:
   /**
    * @brief Constructor that takes in a type.
    */
   ElectionOfficial(string type);

   /**
    * @brief getTypeElection() method loads the file and returns the number of ballots in a string.
    */
   string getTypeElection();

   /**
    * @brief loadFile() method loads the file and returns the number of ballots in a string.
    */
   void loadFile();

   /**
    * @brief help() method provides the user instructions on what to do.
    */
   void help();

   /**
    * @brief CreateIRElection(): method that creates an election of type IR
    * It takes a file name as an argument and set basic information need it to
    * run the election
    * 
    * @param[in] filename It takes a string that constains the name of the 
    * IR election file
    * 
    * @return IR pointer used to then run the election
    */
   IR* CreateIRElection(string filename);

   /**
    * @brief CreateOPLElection(): method that creates an election of type OPL
    * It takes a file name as an argument and set basic information need it to
    * run the election
    * 
    * @param[in] filename It takes a string that constains the name of the 
    * OPL election file
    * 
    * @return OPL pointer used to then run the election
    */
   OPL* CreateOPLElection(string filename);

   /**
    * @brief PerformIRElection(): method that is used to run an IR election
    * once the file entered by the user is of type IR
    * 
    * @param[in] filename It takes a string that constains the name of the 
    * IR election file
    * 
    */
   void PerformIRElection(string filename);

   /**
    * @brief PerformOPLElection(): method that is used to run an IR election
    * once the file entered by the user is of type OPL
    * 
    * @param[in] filename It takes a string that constains the name of the 
    * OPL election file
    * 
    */
   void PerformOPLElection(string filename);

   /**
    * @brief CreatePOElection(): method that creates an election of type PO
    * It takes a file name as an argument and set basic information need it to
    * run the election
    * 
    * @param[in] filename It takes a string that constains the name of the 
    * IR election file
    * 
    * @return PO pointer used to then run the election
    */
   PO* CreatePOElection(string filename);

   /**
    * @brief PerformPOElection(): method that is used to run an IR election
    * once the file entered by the user is of type OPL
    * 
    * @param[in] filename It takes a string that constains the name of the 
    * PO election file
    * 
    */
   void PerformPOElection(string filename);

  private:
 /**
 * @brief A string typeElection that contains the User's type.
 */
    string typeElection;


};

#endif  // ELECTION_OFFICIAL_H_
