/**
 *@file ir.h
 */
#ifndef IR_H_
#define IR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include "election.h"
#include "candidate.h"
#include <map>

using namespace std;

  
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief IR class for Instant-Runoff
 *
 * IR will perform the count of ballots for a IR election
 * It will assign the ballots from an election file to the specific candidate
 * Once the ballots have been read from the election file, it will check if a 
 * winner has been determined or removed the candidate with the lowest vote count,
 * which ballots will be assigned to the next candidate, if any.
 *
 * See the documentation for Election for more information
 */

class IR : public Election {
    public:
        /**
         * @brief Constructor: use to create an IR instance.
         *
         * param[in] filename, takes a string with the name of the election file.
         *
         */
        IR();

        /**
         * @brief GetCandidates: use to create an IR instance.
         *
         * @return vector Candidates for the IR election
         *
         */
        vector<Candidate> GetCandidates();

        /**
         * @brief SolveTie: use to solve a tie during the election.
         *
         * @return integer to be used an index value to return the loser/winner
         *
         */
        int SolveTie(int n);

         /**
         * @brief SetCandidate: used add a candidate to the election.
         *
         *
         */
        void SetCandidate(Candidate candidate);

         /**
         * @brief GetWinner: Getter method to get the winner of an election
         *
         * @return string with the name of the candidate who won the election
         *
         */
        string GetWinner();

         /**
         * @brief SetWinner: Setter method for the winner candidate.
         *
         * param[in] string of the name of the candidate who won the election.
         *
         */
        void SetWinner(string candidate);

         /**
         * @brief CheckWinner: use to determine if the election has a winner
         *
         * @return bool value depending if a winner has been found or not
         *
         */
        bool CheckWinner(map<string, int> &hash);


         /**
         * @brief RedistributeBallots: use to redistribute the ballots of a losing
         * candidate.
         * 
         * param[in] int idx, which is the index of the losing candidate.
         */
        void RedistributeBallots(int idx);

         /**
         * @brief PerformElection: use to get the results of an election.
         *
         *
         */
        void PerformElection();

        /**
         * @brief SetCandidates(): method used to create the Candidate objects
         * in the IR election
         *
         * @param[in] stream is a string with the name of all the candidates
         *
         */
        void SetCandidates(string stream);

        /**
        * @brief GetNumValidBallots: Getter to get the number of valid ballots
         *
         * @return int with the number of valid ballots in the election
         * 
         */
        int GetNumValidBallots();

        /**
         * @brief SetNumBallots: Setter to set the number of valid ballots
         *
         * param[in] int with the number of valid ballots found in the election file
         * 
         */
        void SetNumValidBallots(int numBallots);

        /**
         * @brief IsValidBallot(): method used to verify if a ballot is valid
         *
         * @param[in] ballot is an int vector containing the data of the ballot
         *
         */
        bool IsValidBallot(vector<int> ballot);

        /**
         * @brief AddBallots(): method used to add more ballots from a file to the
         * election
         *
         * @param[in] filename is a string representing the name of the file of a
         * IR election
         *
         */
        void AddBallots(string filename);

        /**
         * @brief AddMultipleFiles(): method used to add ballots from
         * multiple files to a IR election
         *
         */
        void AddMultipleFiles();

    private:
        int numCandidates;
        int numValidBallots;
        vector<Candidate> candidates;
        string winner;
};

#endif // IR_H_