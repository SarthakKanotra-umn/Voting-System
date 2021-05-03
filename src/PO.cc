/**
 * @file PO.cc
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
#include <map>
#include <iomanip>

#include "PO.h"
#include "party.h"
using namespace std;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

PO::PO() {
  numCandidates = 0;
  SetType("PO");
}



void PO::SetNumCandidates(int x) {
  numCandidates = x;
}  //set to numNumCandidates

int PO::GetNumCandidates() {
  return numCandidates;
}   //get numCandidates


void PO::SetCandidatesNames(string n) {
  candidate_names = n;
}  //set to candidates in election file

string PO::GetCandidatesNames() {
  return candidate_names;
}   //get Candidates


int PO::FindPartyIndex(vector<int> ballot){
  for (int i = 0; i<ballot.size(); i++){
    if (ballot[i] == 1){
      return i;
    }
  }
}


void PO::AddBallots(string electionFile){
  ifstream file (electionFile);
    if (file.is_open()){
      string buffer;
      getline(file, buffer); // type
      getline(file, buffer); // number of candidates
      getline(file, buffer); // candidates
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

void PO::SetParties(string buffer){
  string eachCandidate; //store each candidate without ','
  istringstream iss(buffer);

  for (int i = 0; i<GetNumCandidates(); i++) {
    getline(iss, eachCandidate, ']' );
    //rigt now eachCandidate = "[Pike, D" then ", [Foster,D"

    eachCandidate = GetName(eachCandidate);

    Party p1(eachCandidate);
    party.push_back(p1);
  }
  SetPartyVector(party);
}

string PO::GetName(string eachCandidate) {
  string copyEachCandidate = "";
  bool val = false;
  for (int i = 0; i < eachCandidate.length(); i++) {
    if (eachCandidate.at(i) == '[' && !val) {
      val = true;
    }

    else if(val && eachCandidate.at(i) != ','){
      copyEachCandidate += eachCandidate.at(i);
    }

    else if(val && eachCandidate.at(i) == ',' ){
      return copyEachCandidate;
    }
  }
}

void PO::SetPartyVector(vector<Party> parties){
  party = parties;
}

vector<Party> PO::GetPartyVector(){
  return party;
}

void PO::AddMultipleFiles(){
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
}
