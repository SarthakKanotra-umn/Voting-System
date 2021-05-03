/**
 * @file user.cc
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
 
 #include "user.h"
 using namespace std;
 
 /*******************************************************************************
 * Member Functions
 ******************************************************************************/
 
User::User(string type){
  typeUser = type;
}
 
void User::runElection(string user, FILE file){
  if (user == "IR") {
      IR *election = new IR(file);
      election->SetType(this.typeUser);
      election->PerformCount();
      election->DistrubuteSeats();
      election->MakeAuditFile();
              
  } else if (user == "OPL") {
      OPL *election = new OPL(file);
      election->SetType(this.typeUser);
      election->PerformCount();
      election->DistrubuteSeats();
      election->MakeAuditFile();
      
  } else {
      cout << "Please select an election file first" << endl;   
        
  }
}
