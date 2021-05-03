#include "gtest/gtest.h"
#include "../src/opl.h"
#include "../src/election.h"
#include "../src/party.h"
#include "election_official.h"


#include<math.h>
#include<assert.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;



class OPLTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
  virtual void TearDown() {}


};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

// Checks that DefaultConstructor works correctly
 TEST_F(OPLTest, DefaultConstructor) {

   OPL op;

   EXPECT_EQ(op.GetSeats(), 0) << "The numSeats is not correct";
   EXPECT_EQ(op.GetType(), "OPL") << "The filename is not correct";

   OPL op2;

   EXPECT_EQ(op2.GetSeats(), 0) << "The numSeats is not correct";
   EXPECT_EQ(op.GetType(), "OPL") << "The filename is not correct";

 }


// check if SetQuotaSeats and GetQuotaSeats works correctly
TEST_F(OPLTest, SetGetQuotaSeats) {

  OPL op;

  op.SetQuotaSeats(10);

  EXPECT_EQ(op.GetQuotaSeats(), 10) << "The seat quota is not correct";

  op.SetQuotaSeats(100);

  EXPECT_EQ(op.GetQuotaSeats(), 100) << "The seat quota is not correct";
}

// check if SetSeats and GetSeats works correctly
TEST_F(OPLTest, SetGetSeats) {

  OPL op;

  op.SetSeats(5);

  EXPECT_EQ(op.GetSeats(), 5) << "The numSeats is not correct";

  op.SetSeats(10);

  EXPECT_EQ(op.GetSeats(), 10) << "The numSeats is not correct";
}

// check if SetNumCandidates and GetNumCandidates works correctly
TEST_F(OPLTest, SetGetNumCandidates) {

  OPL op;

  op.SetNumCandidates(5);

  EXPECT_EQ(op.GetNumCandidates(), 5) << "The NumCandidates is not correct";

  op.SetNumCandidates(10);

  EXPECT_EQ(op.GetNumCandidates(), 10) << "The NumCandidates is not correct";
}


// check if SetCandidatesNames and GetCandidatesNames works correctly
TEST_F(OPLTest, SetGetCandidateNames) {

  OPL op;

  op.SetCandidatesNames("cand 1");

  EXPECT_EQ(op.GetCandidatesNames(), "cand 1") << "The CandidatesNames is not correct";

  op.SetCandidatesNames("cand 2");

  EXPECT_EQ(op.GetCandidatesNames(), "cand 2") << "The CandidatesNames is not correct";
}


// check if PerformCount works correctly
TEST_F(OPLTest, DistributeSeats) {

  OPL op;

  map<string, int> m1;
  map<string, int>::iterator itr;
  m1.insert(pair<string, int> ("D", 5));
  m1.insert(pair<string, int> ("I", 1));
  m1.insert(pair<string, int> ("R", 3));

  for (itr = m1.begin(); itr!= m1.end(); itr++) {

    if(itr->first == "D") {
      EXPECT_EQ(itr->second, 5) << "The numvotes is not correct";
    }

    else if(itr->first == "R") {
      EXPECT_EQ(itr->second, 3) << "The numvotes is not correct";
    }

    else if(itr->first == "I") {
      EXPECT_EQ(itr->second, 1) << "The numvotes is not correct";
    }
  }
}

// NEED TO ADD UNIT TESTS FOR NEW METHODS THAT DEAL WITH MULTIPLE FILES


// check if FindPartyIndex works correctly
TEST_F(OPLTest, FindPartyIndex) {

  OPL op;

  vector<int> ballot;
  ballot.push_back(1);
  ballot.push_back(0);
  ballot.push_back(0);
  ballot.push_back(0);

  int index = op.FindPartyIndex(ballot);

  EXPECT_EQ(index, 0) << "FindPartyIndex is not correct";
}


// check if AddBallots works correctly
TEST_F(OPLTest, AddBallots) {

  ElectionOfficial eo("OPL");


  OPL* election = eo.CreateOPLElection("OPL.csv");
  election->AddBallots("OPL.csv");  //numBallots = 9

  int num_ballots = election->GetNumBallots();

  EXPECT_EQ(num_ballots, 9) << "FindPartyIndex is not correct";
}

// check if SetParties works correctly
TEST_F(OPLTest, SetParties) {

  OPL *op = new OPL();

  string buffer;
  ifstream file ("OPL.csv");


  getline(file, buffer); // type
  getline(file, buffer); // number of candidates
  op->SetNumCandidates(stoi(buffer));
  getline(file, buffer); // candidates
  op->SetCandidatesNames(buffer);
  op->SetParties(buffer);

  vector<Party> vec = op->GetPartyVector();


  EXPECT_EQ(vec.size(), 6) << "SetParties is not correct";
}


TEST_F(OPLTest, SetGetPartyVector) {

  OPL op;

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


// check if SetHash and GetHash works correctly
TEST_F(OPLTest, SetGetHash) {

  OPL op;

  map<string,int> hash1;

  hash1.insert(pair<string, int> ("name1", 1));
  hash1.insert(pair<string, int> ("name2", 2));
  hash1.insert(pair<string, int> ("name3", 3));

  op.SetHash(hash1);

  map<string,int> hash_output = op.GetHash();

  EXPECT_EQ(hash_output["name1"], 1) << "The Hash is not correct";
  EXPECT_EQ(hash_output["name3"], 3) << "The Hash is not correct";

}


// check if CreateHashParties works correctly
TEST_F(OPLTest, CreateHashParties) {
  ElectionOfficial eo("OPL");

  OPL* election = eo.CreateOPLElection("OPL.csv");
  election->AddBallots("OPL.csv");
  election->CreateHashParties();

  map<string,int> hash_output = op.GetHash();

  EXPECT_EQ(hash_output["D"], 5) << "The Hash is not correct";
  EXPECT_EQ(hash_output["R"], 3) << "The Hash is not correct";

}
