/**
 * @file opl.cc
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstdio>
#include <iomanip>

#include "opl.h"
#include "party.h"
using namespace std;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

OPL::OPL() {
  numSeats = 0;
  SetType("OPL");
}


vector<string> OPL::solveTie(vector<string> p){
  // rand should be between 0 and p.size()
  int randint;

  srand(time(NULL));
  while (p.size() > 1) {

    for (int i=0; i < 10000; i++) {
      randint = rand() % p.size();
    }
    p.erase(p.begin()+randint);
  }
  return p;
}


void OPL::SetQuotaSeats(int quota) {
  quotaSeats = quota;
}  //set to quotaSeats

int OPL::GetQuotaSeats(){
  return quotaSeats;
}   //get quotaSeats

void OPL::SetSeats(int s) {
  numSeats = s;
}  //set to numSeats

int OPL::GetSeats() {
  return numSeats;
}   //get numseats

void OPL::SetNumCandidates(int x) {
  numCandidates = x;
}  //set to numNumCandidates

int OPL::GetNumCandidates() {
  return numCandidates;
}   //get numCandidates


void OPL::SetCandidatesNames(string n) {
  candidate_names = n;
}  //set to candidates in election file

string OPL::GetCandidatesNames() {
  return candidate_names;
}   //get Candidates

void OPL::DistributeSeats() {
  SetQuotaSeats(GetNumBallots()/GetSeats());
  int quota = GetQuotaSeats();
  map<string, int>::iterator itr;

  int ballot_order = 1;
  remainingSeats = GetSeats();  //get the number of seats in the party

  while (remainingSeats > 0) {

    int temp = remainingSeats; //temp variable to check when there is a winner or to solve tie
    int seats;

    //loop to add seats to party based on quota and decrement remaining votes
    for (itr = hash.begin(); itr!= hash.end(); itr++) {
      seats = itr->second/quota;

      itr->second -= quota * seats;   //remaining_votes

      string name = itr->first;

      for (int x =0; x<party.size(); x++) {
        if (name == party.at(x).getName()) {

          party.at(x).addSeat(seats);
          remainingSeats -= seats;
          break;
        }
      }
    }

    //if there is a winner or solve tie is called
    if (remainingSeats == temp) {
      int max = 0;
      vector<string> p1;
      int n;
      for (itr = hash.begin(); itr!= hash.end(); itr++) {
        n = itr->second % quota;
        if (n==max) {
          p1.push_back(itr->first);
        }
        else if (n>max) {
          p1.clear();
          p1.push_back(itr->first);
          max = n;
        }
      }
      if(p1.size() > 1) {
        p1 = solveTie(p1);  //solve the tie randomly
      }
      hash[p1.at(0)]=0;

      //loop to add last seat for reminaing party
      for (int x =0; x<party.size(); x++) {
        if (p1.at(0) == party.at(x).getName()) {
          party.at(x).addSeat(1);
          remainingSeats -= 1;
          break;
        }
      }
    } //end of if remainingSeats == temp

    //each allocation order:
    WriteToAudit("After allocation, " + to_string(ballot_order) + ": \n");

    //loop to write the number of seats a party receives after each and all allocations
    for (int k =0; k<party.size(); k++) {
      if(party.at(k).getSeats() > 0) {

        if(party.at(k).getName() == "D"){
          WriteToAudit("Democratic Party had, " + to_string(party.at(k).getSeats()) + " seat(s) \n");
        }

        else if(party.at(k).getName() == "R"){
          WriteToAudit("Republican Party had, " + to_string(party.at(k).getSeats()) + " seat(s) \n");
        }

        else if(party.at(k).getName() == "I"){
          WriteToAudit("Independent Party had, " + to_string(party.at(k).getSeats()) + " seat(s) \n");
        }

      }
    }//end of for loop above ^^^
    ballot_order++;
  }//end of while remainingSeats>0

  //loop to write % of seats to audit file
  float max = -1.0;
  string partyName;
  for (int k =0; k<party.size(); k++) {
    if(party.at(k).getSeats() > 0) {
      float ans = ((float) party.at(k).getSeats() / (float) GetSeats()) * 100.00;
      if (ans > max){
        max = ans;
        partyName = party.at(k).getName();
      }

      int a = (int) ans;

      if(party.at(k).getName() == "D"){
        WriteToAudit("% of Seats, for Democratic Party, " + to_string(a) + "% \n");
      }

      else if(party.at(k).getName() == "R"){
        WriteToAudit("% of Seats, for Republican Party, " + to_string(a) + "% \n");
      }

      else if(party.at(k).getName() == "I"){
        WriteToAudit("% of Seats, for Independent Party, " + to_string(a) + "% \n");
      }
    }
  }//end of for loop above ^^^
  if (partyName == "D"){
    cout << "Democrats won with " << max << "% of Seats" << endl;
  }
  else if (partyName == "R"){
    cout << "Republicans won with " << max << "% of Seats" << endl;
  }
  else if (partyName == "I"){
    cout << "Independents won with " << max << "% of Seats" << endl;
  }

} //end of DistributeSeats()


int OPL::FindPartyIndex(vector<int> ballot){
  for (int i = 0; i<ballot.size(); i++){
    if (ballot[i] == 1){
      return i;
    }
  }
}

void OPL::AddBallots(string electionFile){
  ifstream file (electionFile);
    if (file.is_open()){
      string buffer;
      getline(file, buffer); // type
      getline(file, buffer); // number of candidates
      getline(file, buffer); // candidates
      getline(file, buffer); // number of seats
      getline(file, buffer); // number of ballots
      SetNumBallots(stoi(buffer));

      vector<Party> party = GetPartyVector();


      while(getline(file, buffer)){
        vector<int> ballot = ConvertStringBallot(buffer);
        int index = FindPartyIndex(ballot);
        party.at(index).addVote();
      }

      SetPartyVector(party);
    }
    else {
        cout << "File not found" << endl;
    }
}

void OPL::SetParties(string buffer){
  string eachCandidate; //store each candidate without ','
  istringstream iss(buffer);

  for (int i = 0; i<GetNumCandidates(); i++) {
    getline(iss, eachCandidate, ']' );
    eachCandidate = eachCandidate.at(eachCandidate.length() - 1);

    Party p1(eachCandidate);
    party.push_back(p1);
  }

  SetPartyVector(party);
}

void OPL::SetPartyVector(vector<Party> parties){
  party = parties;
}

vector<Party> OPL::GetPartyVector(){
  return party;
}

void OPL::AddMultipleFiles(){
  string answer;
  cout << "   Would you like to add another file to this election? (y/n)" << endl;
  cout << ">> ";
  cin >> answer;

  while (answer.compare("y") == 0){
      string filename;
      cout << "   Enter file name" << endl;
      cout << ">> ";
      cin >> filename;
      AddBallots(filename);

      cout << "   Would you like to add another file to this election? (y/n)" << endl;
      cout << ">> ";
      cin >> answer;
  }

  CreateHashParties();

  WriteToAudit("\n");
  map<string, int>::iterator itr;
  WriteToAudit("Number of ballots in election, OPL, " + to_string(GetNumBallots()) + "\n");

  //write number of votes for each party and % of votes they received to audit file
  for (itr = hash.begin(); itr!= hash.end(); itr++) {

    if(itr->first == "D") {
      float ans = ((float) itr->second / (float) GetNumBallots()) * 100.00;
      int a = (int) ans;

      WriteToAudit("Democratic party had, " + to_string(itr->second) + ", votes" + "\n");
      WriteToAudit("% of Votes, for Democratic Party, " + to_string(a) + "% \n");
    }

    else if(itr->first == "R") {
      float ans = ((float) itr->second / (float) GetNumBallots()) * 100.00;
      int a = (int) ans;

      WriteToAudit("Republican party had, " + to_string(itr->second) + ", votes" + "\n");
      WriteToAudit("% of Votes, for Republican Party, " + to_string(a) + "% \n");
    }

    else if(itr->first == "I") {
      float ans = ((float) itr->second / (float) GetNumBallots()) * 100.00;
      int a = (int) ans;

      WriteToAudit("Independent party had, " + to_string(itr->second) + ", votes" + "\n");
      WriteToAudit("% of Votes, for Independent Party, " + to_string(a) + "% \n");
    }
  } //end of for loop to write to audit file

  WriteToAudit("\n\n");
}

void OPL::SetHash(map<string, int> hash_) {
  hash = hash_;
}

map<string, int> OPL::GetHash(){
  return hash;
}

void OPL::CreateHashParties(){
  map<string, int> m1;
  map<string, int>::iterator itr;
  for (int k =0; k<party.size(); k++) {
    Party p = party.at(k);
    if (m1.count(p.getName()) > 0) {
      continue;
    }
    else {
      m1.insert(pair<string, int> (p.getName(), p.getNumVotes()));
      for (int l=k+1; l<party.size(); l++) {
        if (party.at(l).getName() == p.getName()) {
          itr = m1.find(p.getName());
          if (itr!=m1.end()) {
            itr->second += party.at(l).getNumVotes();
          }
        }
      }
    }
  }

  hash = m1;
  SetHash(hash);
}
