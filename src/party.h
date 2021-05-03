/**
 * @file party.h
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */
#ifndef PARTY_H_
#define PARTY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Party class to represent the respective Parties.
 *
 *
 * Party class used to represent a party in the
 * election. This is only used for Open Party
 * Listing voting to keep count of the votes
 * received by a party.
 *
 *
 */
class Party {
  public:
    /**
     * @brief DefaultConstructor: calls to /ref Party can setup an instance of a Party
     * in the voting system.
     *
     */
    Party();

    /**
     * @brief Constructor: calls to /ref Party can setup an instance of a Party
     * in the voting system.
     *
     * param[in] n, takes in the name of a Party.
     *
     */
    Party(string n);

    /**
    * @brief getName: calls to /ref getName method returns the name of the Party.
    *
    * @return name of the Party whose instance has been created.
    */
    string getName();

    /**
    * @brief: getTotalVotes: calls to /ref getTotalVotes method returns total
    * votes for a party.
    *
    * @return numVotes which is the total votes a Party receieves.
    */
    int getNumVotes();

    /**
    * @brief: getSeats: calls to /ref getSeats method returns total
    * seats for a party.
    *
    * @return seats which is the total seats a Party receieves.
    */
    int getSeats();

    /**
     * @brief addVote: calls to /ref addVote increments the number of votes
     * for a party in the voting system.
     *
     */
    void addVote();

    /**
     * @brief addSeat: calls to /ref addSeat increments the number of seats
     * for a party in the voting system.
     *
     */
    void addSeat(int s);

    /**
     * @brief setSeats: calls to /ref setSeats sets the number of seats
     * for a party to the number of seats provided in the voting system.
     * param[in] a, takes in number of seats as argument to set to seats field
     *
     */
    void setSeats(int a);


  private:

    string nameParty;
    int numVotes;
    int seats;

};

#endif  // PARTY_H_
