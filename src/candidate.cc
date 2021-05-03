/**
 * @file candidate.cc
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "candidate.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Candidate::Candidate() {
  name = "";
  count = votes.size();
}

Candidate::Candidate(std::string name) {
  this->name = name;
  count = votes.size();
}

std::string Candidate::GetName() {
  // Method to get name of Candidate
  return name;
}

std::vector<Ballot> Candidate::GetVotes() {
  // Method to get list of vote Ballots
  return votes;
}

int Candidate::TotalVotes() {
  // Method to get total number of votes for current Candidate instance
  return count;
}

void Candidate::SetTotalVotes(int i) {
  // Method to set total number of votes for current Candidate instance
  count = i;
}

void Candidate::AddVote(Ballot ballot){
  // Method to add vote ballot to the current list of votes
  votes.push_back(ballot);
  count++;
}

void Candidate::SetCountToZero(){
  // Method to set current vote count to zero
  count=0;
}

void Candidate::IncrementCount(){
  // Method to increment vote count
  count++;
}

void Candidate::SetVotes(std::vector<Ballot> v){
  // Method to update list of ballots
  votes = v;
}
