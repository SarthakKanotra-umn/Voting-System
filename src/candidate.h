/**
 * @file candidate.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef CANDIDATE_H_
#define CANDIDATE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include "ballot.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Candidate class to represent candidates within the voting system.
 *
 *
 * The Candidate class is used to represent candidates of an election. This is 
 * only used in the Instant Runoff voting since each individual candidate has 
 * the potential to win the election.
 *
 */

class Candidate {
  public:
    /**
     * @brief DefaultConstructor: calls to /ref Candidate can setup an instance of a Candidate
     * in the voting system.
     *
     */
    Candidate();                            // Default constructor

    /**
     * @brief Constructor: calls to /ref Candidate can setup an instance of a Candidate
     * in the voting system.
     *
     * param[in] name, takes in the name of a Candidate
     *
     */
    Candidate(std::string name);            // Constructor

    /**
    * @brief GetName: calls to /ref GetName method returns the name of the Candidate.
    *
    * @return name of the Candidate whose instance has been created.
    */
    std::string GetName();                  // Method to get name of Candidate

    /**
    * @brief GetVotes: calls to /ref GetVotes method returns the list of the Ballots.
    *
    * @return vector of votes of the Ballots for the Candidate instance that has been created.
    */
    std::vector<Ballot> GetVotes();         // Method to get the current list of Ballots

    /**
     * @brief TotalVotes: calls to /ref TotalVotes returns the current number of total votes
     * for a Candidate in the voting system.
     *
     * @return number of votes for the Candidate instance that has been created.
     */
    int TotalVotes();                       // Method to get total number of votes for current Candidate instance
    
    /**
     * @brief SetTotalVotes: calls to /ref SetTotalVotes sets the current number of total votes
     * for a Candidate in the voting system.
     *
     */
    void SetTotalVotes(int i);              // Method to set total number of votes for current Candidate instance

    /**
     * @brief AddBallot: calls to /ref AddBallot adds a vote Ballot to the current list of votes
     * for a Candidate in the voting system.
     *
     * param[in] ballot, takes in a Ballot object.
     *
     */
    void AddVote(Ballot ballot);          // Method to add vote ballot to the current list of votes

    /**
     * @brief SetCountToZero: calls to /ref SetCountToZero sets the current count variable, used to determine
     * the number of votes a candidates, to zero.
     *
     */
    void SetCountToZero();                  // Method to set current vote count to zero

    /**
     * @brief SetVotes: calls to /ref SetVotes sets the current list of votes stored in the votes variable
     * to the new list of Ballots, v.
     *
     * param[in] v, takes in vector of vote Ballots.
     *
     */
    void SetVotes(std::vector<Ballot> v);   // Method to update list of ballots
    
    /**
     * @brief IncrementCount: calls to /ref IncrementCount increments the number of votes a candidate has.
     *
     */
    void IncrementCount();                    // Method to increment vote count

  private:
    std::string name;
    int count;                          
    std::vector<Ballot> votes;

};
#endif // CANDIDATE_H_
