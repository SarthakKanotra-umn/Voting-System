/**
 * @file opl.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef OPL_H_
#define OPL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "party.h"
#include "election.h"
#include <map>

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Open Party List voting which inherits from Election.
 *
 *
 * Open Party Listing will run the election type OPL.
 * This is to read in the election file when the type
 * specified is OPL. It then counts and performs the
 * vote check and assignment of seats. A method to solve
 * tie is called if a tie need to be randomly solved.
 *
 */
class OPL : public Election {
  public:

    /**
     * @brief DefaultConstructor: calls to /ref OPL can setup an OPl election
     * in the voting system.
     *
     * param[in] filename, takes in a filename to open the provided election file.
     *
     */
    OPL();


    /**
     * @brief solveTie: calls to /ref solveTie solves a tie by randomly
     * in the voting system.
     *
     * param[in] p, vector of strings that takes in party names that
     * need the tie to be solved.
     *
     */
    vector<string> solveTie(vector<string> p);


    /**
     * @brief DistributeSeats: calls to /ref DistributeSeats uses data collected
     * from /ref PerformCount to distribute the required seats to the parties.
     * It also checks if there is a tie and calls /ref solveTie to solve
     * the tie randomly.
     *
     */
    void DistributeSeats();

    /**
     * @brief SetQuotaSeats: calls to /ref SetQuotaSeats sets the seat quota of
     * the OPL election to the quota calculated by dividing the total number of
     * valid votes by the number of seats provided in the election file.
     *
     * param[in] quota, takes in the quota and sets it to the field quotaSeats.
     *
     */
    void SetQuotaSeats(int quota);

    /**
     * @brief GetQuotaSeats: calls to /ref GetQuotaSeats returns the
     * seat quota set and calculated by divding the total number of
     * valid votes by the number of seats provided in the election file.
     *
     * @return the seat quota calculated by the method described above.
     *
     */
    int GetQuotaSeats();

    /**
     * @brief SetSeats: calls to /ref SetSeats sets the number of Seats
     * provided in the election file to the field numSeats.
     *
     * param[in] s, the number of seats obtained from the election file.
     *
     */
    void SetSeats(int s);

    /**
     * @brief GetSeats: calls to /ref GetSeats returns the number of Seats
     * in the OPL election file.
     *
     * @return the number of seats in the election for OPL.
     *
     */
    int GetSeats();

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
     * of candidates in the OPL election file.
     *
     * @return the number of candidates in the election for OPL.
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
     * name of candidates in the OPL election file.
     *
     * @return the name of candidates in the election for OPL.
     *
     */
    string GetCandidatesNames();   //get Candidates

    /**
     * @brief AddBallots: method used to add new ballots from a file
     *
     * @param[in] filename is a string reprensenting the name of a OPL election
     * file.
     *
     */
    void AddBallots(string filename);

    /**
     * @brief SetParties: method used to create the party objects for the
     * OPL election
     *
     * @param[in] buffer is a string representing the name of the parties.
     *
     */
    void SetParties(string buffer);

    /**
     * @brief AddMultipleFiles: method used to read in multiple files
     * for the OPL election
     *
     */
    void AddMultipleFiles();

    /**
     * @brief CreateHashParties: method used to create a hash tables with
     * the votes that each party received
     *
     */
    void CreateHashParties();

    /**
     * @brief FindPartyIndex: method used to find the index of the party that
     * receive the vote from a ballot
     *
     * @param[in] ballot is a vector of integer representing the value of a ballot
     *
     * @return integer value that it is used as in index to add the vote to the
     * party in the field party at the index of the value returned
     *
     */
    int FindPartyIndex(vector<int> ballot);

    /**
     * @brief SetPartyVector: method used to update the value of party
     *
     * @param[in] parties is a vector<Party> representing all the parties
     * in the OPL election
     *
     */
    void SetPartyVector(vector<Party> parties);

    /**
     * @brief GetPartyVector: method used to obtain the value of the
     * party field
     *
     * @return vector<Party> with the value of the field party
     *
     */
    vector<Party> GetPartyVector();

    /**
     * @brief SetHash: method used to set the hash map to the value passed.
     *
     * @param[in] hash_ is a hash map that is to be set to the variable hash.
     *
     */
    void SetHash(map<string, int> hash_);

    /**
     * @brief GetHash: method used to get the hash map.
     *
     * @return  public variable hash which is a hash map is returned.
     *
     */
    map<string, int> GetHash();


  private:
    vector<Party> party;  //vector of type Party representing various Parties ---- add to UML
    int numSeats;        //total number of seats in the voting system
    int remainingSeats; //number of remainging seats
    int quotaSeats;    // result of totalValidVotes / numSeats --- add to UML
    int numCandidates; //need for audit file ; used in performcount while reading from file --- add to UML
    string candidate_names;  //for audit file
    map<string, int> hash;
};

#endif  // OPL_H_
