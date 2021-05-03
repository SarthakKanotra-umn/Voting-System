#include "gtest/gtest.h"
#include "../src/PO.h"
#include "../src/election.h"
#include "../src/party.h"
#include "../src/election_official.h"

#include<math.h>
#include<assert.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;



class POTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
  virtual void TearDown() {}


};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

// Checks that DefaultConstructor works correctly
 TEST_F(POTest, DefaultConstructor) {

   PO op;

   EXPECT_EQ(op.GetNumCandidates(), 0) << "The filename is not correct";
   EXPECT_EQ(op.GetType(), "PO") << "The filename is not correct";


   PO op2;

   EXPECT_EQ(op2.GetNumCandidates(), 0) << "The filename is not correct";
   EXPECT_EQ(op.GetType(), "PO") << "The filename is not correct";

 }


// check if SetNumCandidates and GetNumCandidates works correctly
TEST_F(POTest, SetGetNumCandidates) {

  PO op;

  op.SetNumCandidates(5);

  EXPECT_EQ(op.GetNumCandidates(), 5) << "The NumCandidates is not correct";

  op.SetNumCandidates(10);

  EXPECT_EQ(op.GetNumCandidates(), 10) << "The NumCandidates is not correct";
}


// check if SetCandidatesNames and GetCandidatesNames works correctly
TEST_F(POTest, SetGetCandidateNames) {

  PO op;

  op.SetCandidatesNames("cand 1");

  EXPECT_EQ(op.GetCandidatesNames(), "cand 1") << "The CandidatesNames is not correct";

  op.SetCandidatesNames("cand 2");

  EXPECT_EQ(op.GetCandidatesNames(), "cand 2") << "The CandidatesNames is not correct";
}

// check if FindPartyIndex works correctly
TEST_F(POTest, FindPartyIndex) {

  PO op;

  vector<int> ballot;
  ballot.push_back(1);
  ballot.push_back(0);
  ballot.push_back(0);
  ballot.push_back(0);

  int index = op.FindPartyIndex(ballot);

  EXPECT_EQ(index, 0) << "FindPartyIndex is not correct";
}

// check if AddBallots works correctly
TEST_F(POTest, AddBallots) {

  ElectionOfficial eo("PO");


  PO* election = eo.CreatePOElection("PO.csv");
  election->AddBallots("PO.csv");  //numBallots = 10

  int num_ballots = election->GetNumBallots();

  EXPECT_EQ(num_ballots, 10) << "FindPartyIndex is not correct";
}

// check if SetParties works correctly
TEST_F(POTest, SetParties) {

  PO *po = new PO();

  string buffer;
  ifstream file ("PO.csv");

  getline(file, buffer); // type
  getline(file, buffer); // number of candidates
  po->SetNumCandidates(stoi(buffer));
  getline(file, buffer); // candidates
  po->SetCandidatesNames(buffer);
  po->SetParties(buffer);

  vector<Party> vec = po->GetPartyVector();


  EXPECT_EQ(vec.size(), 6) << "SetParties is not correct";
}

// check if GetName works correctly
TEST_F(POTest, GetName) {

  PO op;

  string output =   op.GetName("[Pike, D"); //returns string "Pike"

  EXPECT_EQ(output, "Pike") << "GetName is not correct";
}

// check if SetPartyVector and GetPartyVector works correctly
TEST_F(POTest, SetGetPartyVector) {

  PO op;

  vector<Party> vec;
  vector<Party> output;

  Party p1("Name 1");
  Party p2("Name 2");
  Party p3("Name 3");

  vec.push_back(p1);
  vec.push_back(p2);

  op.SetPartyVector(vec);

  output = op.GetPartyVector();

  EXPECT_EQ(output[0].getName(), "Name 1") << "The PartyVector is not correct";
  EXPECT_EQ(output[1].getName(), "Name 2") << "The PartyVector is not correct";

  vec.clear();
  output.clear();

  vec.push_back(p3);

  op.SetPartyVector(vec);

  output = op.GetPartyVector();

  EXPECT_EQ(output[0].getName(), "Name 3") << "The PartyVector is not correct";
}
