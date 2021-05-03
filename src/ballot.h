/**
 * @file ballot.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef BALLOT_H_
#define BALLOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Ballot class to hold individual voting ballots.
 *
 *
 * Ballots will have a vecotr of their vote along with a unique
 * id and a rank. This allows for keeping track of the vote, 
 * identifying the ballot, and keeping track of the rank.
 *
 */

class Ballot {               

  public:
    static int id_count;                  // Variable to generate new id number for Ballot instances
    /**
     * @brief DefaultConstructor: calls to /ref Ballot can setup an instance of a Ballot
     * in the voting system.
     *
     */
    Ballot();                             // Default constructor

    /**
     * @brief Constructor: calls to /ref Ballot can setup an instance of a Ballot
     * in the voting system.
     *
     * param[in] vote, takes in vector of votes.
     *
     */
    Ballot(std::vector<int> vote);        // Constructor 

    /**
    * @brief GetId: calls to /ref GetId method returns the unique ID of the Ballot.
    *
    * @return ID of the Ballot instance that has been created.
    */
    int GetId() const;                    // Method to get unique ballot ID

    /**
    * @brief GetRank: calls to /ref GetRank method returns the rank of the Ballot.
    *
    * @return rank of the Ballot instance that has been created.
    */
    int GetRank() const;                  // Method to get rank of current ballot

    /**
    * @brief GetVote: calls to /ref GetVote method returns the votes of the Ballot.
    *
    * @return vector of votes of the Ballot instance that has been created.
    */
    std::vector<int> GetVote() const;     // Method to get the vote

    /**
     * @brief IncrementRank: calls to /ref IncrementRank increments the rank 
     * for a Ballot in the voting system.
     *
     */
    void IncrementRank();                 // Method to increment rank value

    /**
    * @brief SetRank: calls to /ref SetRank method sets the rank of the Ballot.
    *
    * param[in] rank, takes in new rank value as int.
    */
    void SetRank(int rank);               // Method to set rank of current ballot

  private:
    int id;
    int rank;
    std::vector<int> vote;
};

#endif // BALLOT_H_