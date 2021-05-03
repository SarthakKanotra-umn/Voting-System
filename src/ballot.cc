/**
 * @file ballot.cc
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ballot.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Ballot::Ballot() {
  id = id_count;
  rank = 1;
  id_count++;
}

Ballot::Ballot(std::vector<int> vote) {
  id = id_count;
  rank = 1;
  this->vote = vote;
  id_count++;
}

// Initialize id_count to generate ID #'s
int Ballot::Ballot::id_count = 0;

int Ballot::GetId() const {
  // Method to get unique ballot ID
  return id;
}

int Ballot::GetRank() const {
  // Method to get rank of current ballot
  return rank;
}

std::vector<int> Ballot::GetVote() const {
  // Method to get the vote
  return vote;
}

void Ballot::IncrementRank() {
  // Method to increment rank value
  rank++;
}

void Ballot::SetRank(int rank_){
  // Method to set rank of current ballot
  rank = rank_;
}
