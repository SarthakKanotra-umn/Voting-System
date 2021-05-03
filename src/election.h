/**
 *@file election.h
 */
#ifndef ELECTION_H_
#define ELECTION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

  
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating elections.
 *
 * This class can be used as the base for all election in our election system.
 * 
 */

class Election {
  public:
    /**
     * @brief DefaultConstructor: Create a new election and creates some default
     * values for the election fields.
     *
     */
    Election();

    /**
     * @brief SetType: Setter to set the type of election
     *
     * param[in] string that determine the type of election.
     * 
     */
    void SetType(string type);

    /**
     * @brief SetNumBallots: Setter to set the number of ballots
     *
     * param[in] int with the number of ballots found in the election file
     * 
     */
    void SetNumBallots(int numBallots);

    /**
     * @brief GetType: Getter to get the type of election
     *
     * @return string with the type of election.
     * 
     */
    string GetType();

    /**
     * @brief GetNumBallots: Getter to get the number of ballots
     *
     * @return int with the number of ballots in the election
     * 
     */
    int GetNumBallots();

    /**
     * @brief GetAuditFile: Getter to get the name of the audit file
     *
     * @return string with the name of the audit file
     * 
     */
    string GetAuditFile();

    void AddNewBallots(int newBallots);

    /**
     * @brief WriteToAudit: used to solve a tie during the election.
     *
     * @param[in] string with the message that should be added to 
     * audit file
     *
     */
    void WriteToAudit(string s);

    /**
     * @brief ConvertStringBallot(): method used to create a vector<int>
     * with the values of the ballot read from the csv file
     *
     * @param[in] string that represents a ballot
     * 
     * @return vector<int> that represents a ballot
     *
     */
    vector<int> ConvertStringBallot(string ballot);

  private:
    string type;
    int numBallots;
    string auditFile;
};

#endif // ELECTION_H_