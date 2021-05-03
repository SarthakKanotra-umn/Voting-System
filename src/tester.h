/**
 * @file tester.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef TESTER_H_
#define TESTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "user.h"
 #include "opl.h"
 #include "ir.h"

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Tester class implementation
 *
 * This class contains methods to test each of the election types, namely Instant Runoff (IR)
 * and Open Party Listing (OPL). The testers of the Voting system may utilize the setter functions
 * to test additonal election files outside of the provieded files.
 *
 */
 
class Tester {
  public:
   /**
 * @brief DefaultConstructor: calls to /ref Tester can setup an instance of a Tester
     * in the voting system.
 */
    Tester();
    
 /**
 * @brief RunOPL() method runs the OPL election using the default file OPL.csv.
 */    
    void RunOPL();
    
 /**
 * @brief RunOPL() method runs the OPL election using the default file IR.csv.
 */
    void RunIR();
 /**
 * @brief SetOPLFile() method prompts user to enter a new test file and updates the respective
 * variable containing the OPL election file within Tester.
 */
    void SetOPLFile();
    
 /**
 * @brief SetIRFile() method prompts user to enter a new test file and updates the respective
 * variable containing the OPL election file within Tester.
 */
    void SetIRFile();

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


  private: 
 /**
 * @brief A string OPLFile that contains filename for OPL elections.
 */
    string OPLFile;
 /**
 * @brief A string OPLFile that contains filename for OPL elections.
 */
    string IRFile;
 /**
 * @brief A integer to track the number of ballots for the IR election tests.
 */
    int numBallotsIR;
 /**
 * @brief A integer to track the number of ballots for the OPL election tests.
 */
    int numBallotsOPL;
};

#endif  // TESTER_H_
