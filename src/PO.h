/**
 * @file PO.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef PO_H_
#define PO_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include<fstream>
#include <vector>
#include <string>
#include "party.h"
#include "election.h"
using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Popularity Only voting which inherits from Election.
 *
 *
 * Popularity Only will run the election type PO.
 * This is to read in the election file when the type
 * specified is PO. It then counts and performs the
 * vote count to compute winner. A method to solve
 * tie is called if a tie need to be randomly solved.
 *
 */

 class PO : public Election {
  public:

    /**
     * @brief Constructor: calls to /ref PO can setup an PO election
     * in the voting system.
     *
     * param[in] filename, takes in a filename to open the provided election file.
     *
     */
    PO();


    /**
     * @brief SetNumCandidates: calls to /ref SetNumCandidates sets the number
     * of candidates in the election file to the field numCandidates.
     *
     * param[in] x, the number of candidates obtained from the election file.
     *
     */
    void SetNumCandidates(int x);

    /**
     * @brief GetNumCandidates: calls to /ref GetNumCandidates returns the number
     * of candidates in the PO election file.
     *
     * @return the number of candidates in the election for PO.
     *
     */
    int GetNumCandidates();   //get numCandidates

    /**
     * @brief SetCandidatesNames: calls to /ref SetCandidatesNames sets the
     * name of candidates in the election file to the field candidate_names.
     *
     * param[in] n, string that takes in the candidates' names.
     *
     */
    void SetCandidatesNames(string n);  //set to candidates in election file

    /**
     * @brief GetCandidatesNames: calls to /ref GetCandidatesNames returns the
     * name of candidates in the PO election file.
     *
     * @return the name of candidates in the election for PO.
     *
     */
    string GetCandidatesNames();   //get Candidates

    /**
     * @brief AddBallots: calls to /ref AddBallots adds the ballots from multiple
     * files entered for an election to read in ballots casted at different locations.
     *
     * @param[in] filename the filename from which ballots are to be read from.
     *
     */
    void AddBallots(string filename);

    /**
     * @brief SetParties: calls to /ref SetParties sets/creates the vector with candidates.
     *
     * @param[in] buffer the string from which candidates vector are created.
     *
     */
    void SetParties(string buffer);

    /**
     * @brief AddMultipleFiles: calls to /ref AddMultipleFiles reads in from multiple
     * files entered for an election casted at different locations.
     *
     *
     */
    void AddMultipleFiles();

    /**
     * @brief SetPartyVector: calls to /ref SetPartyVector sets the party vector
     * to the vector<Party> passed in as argument.
     *
     * @param[in] parties the vector<Party> to which party is set to.
     *
     */
    void SetPartyVector(vector<Party> parties);

    /**
     * @brief GetPartyVector: calls to /ref GetPartyVector gets the party vector set
     * to be used.
     *
     * @return the vector<Party> party is set to.
     *
     */
    vector<Party> GetPartyVector();

    /**
     * @brief GetName: calls to /ref GetName gets the name of each candidate to be added to
     * the party vector.
     *
     * @param[in] eachCandidate string that it reads in to create a vector of candidate names.
     *
     * @return string that is the candidates name to be added to vector<Party>
     *
     */
    string GetName(string eachCandidate); //get name for candidate to store in vector

    /**
     * @brief FindPartyIndex: calls to /ref FindPartyIndex returns the index where the vote for
     * a given candidate should be added to.
     *
     * @param[in] ballot the vector<int> from which ballots are checked to add to a candidate.
     *
     * @return an integer indicating the index at which a candidate's vote count is incremented.
     *
     */
    int FindPartyIndex(vector<int> ballot);


  private:
    vector<Party> party;  //vector of type Party representing various Parties ---- add to UML
    int numCandidates; //need for audit file ; used in performcount while reading from file --- add to UML
    string candidate_names;  //for audit file
    map<string, int> hash;
};

#endif  // PO_H_
