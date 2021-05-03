#include "gtest/gtest.h"
#include <vector>
#include "../src/ir.h"
#include "../src/candidate.h"
#include "../src/ballot.h"
#include "../src/election.h"
#include "../src/election_official.h"
#include "../src/opl.h"
#include "../src/party.h"
#include "../src/PO.h"
#include <iostream>
#include <map>
#include<math.h>
#include<assert.h>


class BallotTest : public ::testing::Test{
    public:
        void SetUp(){

    }
};

class OPLTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
  virtual void TearDown() {}


};

class CandidateTest : public ::testing::Test{
    public:
        void SetUp(){

    }
};

class IR_TEST : public ::testing::Test{
    public:
        void SetUp(){

    }
};


class Election_TEST : public ::testing::Test{
    public:
        void SetUp(){

    }
};

class ELECTION_OFFICIAL_TEST : public ::testing::Test{
    public:
        void SetUp(){

    }
};

class PartyTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
  virtual void TearDown() {}


};

class POTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
  virtual void TearDown() {}


};


TEST(BallotTest, DefaultConstructorTest) {
  Ballot b1;
  EXPECT_EQ(b1.GetId(), 0);
  EXPECT_EQ(b1.GetRank(), 1);
  EXPECT_EQ(b1.GetVote().size(), 0);
}

TEST(BallotTest, ConstructorTest) {
  std::vector<int> vote{1, 2, 3, 4};
  Ballot b2(vote);
  EXPECT_EQ(b2.GetId(), 1);
  EXPECT_EQ(b2.GetRank(), 1);
  EXPECT_EQ(b2.GetVote().size(), 4);
}

TEST(BallotTest, GetIdTest) {
  Ballot b3;
  Ballot b4;
  Ballot b5;

  EXPECT_EQ(b3.GetId(), 2);
  EXPECT_EQ(b4.GetId(), 3);
  EXPECT_EQ(b5.GetId(), 4);
}

TEST(BallotTest, IncrementRankTest) {
  Ballot b3;
  Ballot b4;
  Ballot b5;
  b3.IncrementRank();
  b3.IncrementRank();
  b4.IncrementRank();
  b5.IncrementRank();
  b5.IncrementRank();

  EXPECT_EQ(b3.GetRank(), 3);
  EXPECT_EQ(b4.GetRank(), 2);
  EXPECT_EQ(b5.GetRank(), 3);
}

TEST(BallotTest, GetSetRankTest) {
  Ballot b3;
  Ballot b4;
  Ballot b5;
  b3.SetRank(3);
  b4.SetRank(2);
  b5.SetRank(3);

  EXPECT_EQ(b3.GetRank(), 3);
  EXPECT_EQ(b4.GetRank(), 2);
  EXPECT_EQ(b5.GetRank(), 3);
}

TEST(BallotTest, GetVoteTest) {
  std::vector<int> vote{1, 2, 3, 4};
  Ballot b2(vote);

  EXPECT_EQ(b2.GetVote(), vote);
}

TEST_F(IR_TEST, CreateIRElection){
    IR ir;

    string output1 = ir.GetWinner();
    int output2 = ir.GetNumBallots();
    string output3 = ir.GetType();
    int output4 = ir.GetNumValidBallots();

    ASSERT_EQ(output1, "None");
    ASSERT_EQ(output2, 0);
    ASSERT_EQ(output3, "IR");
    ASSERT_EQ(output4, 0);
}

TEST_F(IR_TEST, AddCandidates){
    IR ir;

    ir.SetCandidates("Rosen (D), Kleinberg (R), Chou (I), Royce (L)");

    int output1 = ir.GetCandidates().size();
    vector<Candidate> candidates = ir.GetCandidates();
    string output2 = candidates[0].GetName();
    int output3 = candidates[0].GetVotes().size();

    ASSERT_EQ(output1, 4);
    ASSERT_EQ(output2, "Rosen(D)");
    ASSERT_EQ(output3, 0);
}

TEST_F(IR_TEST, SetWinner){
    IR ir;

    ir.SetWinner("a");

    string output1 = ir.GetWinner();

    ASSERT_EQ(output1, "a");

}

TEST_F(IR_TEST, BallotValidation){
    IR* ir = new IR();

    string buffer;
    ifstream file ("IR_validation.csv");

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    getline(file, buffer); // candidates
    ir->SetCandidates(buffer);
    getline(file, buffer); // number of ballots
    file.close();

    ir->AddBallots("IR_validation.csv");

    int output1 = ir->GetNumValidBallots();

    ir->AddBallots("IR_validation.csv");

    int output2 = ir->GetNumValidBallots();

    ASSERT_EQ(output1, 7);
    ASSERT_EQ(output2, 14);
}

TEST_F(IR_TEST, CheckWinner){
    IR ir;
    ir.SetNumValidBallots(7);
    map<string,int> hash1;
    hash1["A"] = 3;
    hash1["B"] = 1;
    hash1["C"] = 2;
    hash1["D"] = 1;

    bool output1 = ir.CheckWinner(hash1);

    ir.SetNumValidBallots(-ir.GetNumValidBallots());
    ir.SetNumValidBallots(5);
    map<string,int> hash2;
    hash2["A"] = 3;
    hash2["B"] = 0;
    hash2["C"] = 2;
    hash2["D"] = 0;

    bool output2 = ir.CheckWinner(hash2);

    ASSERT_EQ(output1, false);
    ASSERT_EQ(output2, true);
}

TEST_F(IR_TEST, PerformElection){
    IR* ir = new IR();
    string buffer;
    ifstream file ("IR.csv");

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    getline(file, buffer); // candidates
    ir->SetCandidates(buffer);
    getline(file, buffer); // number of ballots
    file.close();

    ir->AddBallots("IR.csv");
    ir->PerformElection();

    string output1 = ir->GetWinner();

    ASSERT_EQ(output1, "Rosen(D)");
}

TEST_F(IR_TEST, RedistributeBallots){
    IR* ir = new IR();
    string buffer;
    ifstream file ("IR.csv");

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    getline(file, buffer); // candidates
    ir->SetCandidates(buffer);
    getline(file, buffer); // number of ballots
    file.close();

    ir->AddBallots("IR.csv");
    ir->RedistributeBallots(3);

    int output1 = ir->GetCandidates().at(3).GetVotes().size();
    int output2 = ir->GetCandidates().at(0).GetVotes().size();

    ASSERT_EQ(output1, 0);
    ASSERT_EQ(output2, 4);
}

TEST_F(IR_TEST, RedistributeToLosingCandidate){
    IR* ir = new IR();
    string buffer;
    ifstream file ("IR.csv");

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    getline(file, buffer); // candidates
    ir->SetCandidates(buffer);
    getline(file, buffer); // number of ballots
    file.close();

    ir->AddBallots("IR.csv");
    ir->RedistributeBallots(2);

    int output1 = ir->GetCandidates().at(2).TotalVotes();
    int output2 = ir->GetCandidates().at(3).TotalVotes();
    int output3 = ir->GetCandidates().at(0).TotalVotes();

    ASSERT_EQ(output1, 0);
    ASSERT_EQ(output2, 3);
    ASSERT_EQ(output3, 4);
}

TEST_F(IR_TEST, AddMultipleFiles){
    IR* ir = new IR();

    string buffer;
    ifstream file ("IR.csv");

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    getline(file, buffer); // candidates
    ir->SetCandidates(buffer);
    getline(file, buffer); // number of ballots
    file.close();

    ir->AddBallots("IR.csv");

    int output1 = ir->GetNumBallots();

    ir->AddBallots("IR.csv");

    int output2 = ir->GetNumBallots();

    ASSERT_EQ(output1, 7);
    ASSERT_EQ(output2, 14);
}

TEST(CandidateTest, DefaultConstructorTest) {
  Candidate c1;

  EXPECT_EQ(c1.GetName(), "");
  EXPECT_EQ(c1.TotalVotes(), 0);
}

TEST(CandidateTest, ConstructorTest) {
  Candidate c2("Bob");
  EXPECT_EQ(c2.GetName(), "Bob");
  EXPECT_EQ(c2.TotalVotes(), 0);
}

TEST(CandidateTest, AddVoteTest) {
  Candidate c1;
  std::vector<int> v1{1,2,3,4};
  std::vector<int> v2{3,4,1,2};
  Ballot b1(v1);
  Ballot b2(v2);
  c1.AddVote(b1);
  c1.AddVote(b2);
  EXPECT_EQ(c1.TotalVotes(), 2);
}

TEST(CandidateTest, GetVotesTest) {
  Candidate c1;
  std::vector<int> v1{1,2,3,4};
  std::vector<int> v2{3,4,1,2};
  Ballot b1(v1);
  Ballot b2(v2);
  c1.AddVote(b1);
  c1.AddVote(b2);

  std::vector<Ballot> b;
  b.push_back(b1);
  b.push_back(b2);
  EXPECT_EQ(c1.GetVotes().at(0).GetVote(), b.at(0).GetVote());
}

TEST(CandidateTest, SetTotalVotesTest) {
  Candidate c1;

  c1.SetTotalVotes(2);

  EXPECT_EQ(c1.TotalVotes(), 2);
}

TEST(CandidateTest, SetCountToZeroTest) {
  Candidate c1;
  std::vector<int> v1;
  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);
  std::vector<int> v2;
  v2.push_back(3);
  v2.push_back(4);
  v2.push_back(1);
  v2.push_back(2);
  Ballot b1(v1);
  Ballot b2(v2);
  c1.AddVote(b1);
  c1.AddVote(b2);

  c1.SetCountToZero();

  EXPECT_EQ(c1.TotalVotes(), 0);
}

TEST(CandidateTest, SetVotesTest) {
  Candidate c1;
  std::vector<int> v1;
  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);
  std::vector<int> v2;
  v2.push_back(3);
  v2.push_back(4);
  v2.push_back(1);
  v2.push_back(2);
  Ballot b1(v1);
  Ballot b2(v2);
  c1.AddVote(b1);
  c1.AddVote(b2);

  std::vector<int> vote1;
  vote1.push_back(1);
  vote1.push_back(0);
  vote1.push_back(0);
  vote1.push_back(2);
  Ballot new_ballot(vote1);

  std::vector<Ballot> v;
  v.push_back(new_ballot);

  c1.SetVotes(v);

  EXPECT_EQ(c1.GetVotes().at(0).GetVote(), v.at(0).GetVote());
}

TEST(CandidateTest, IncrementCountTest) {
  Candidate c1;
  c1.IncrementCount();

  Candidate c2;
  c2.IncrementCount();
  c2.IncrementCount();

  EXPECT_EQ(c1.TotalVotes(), 1);
  EXPECT_EQ(c2.TotalVotes(), 2);
}

TEST_F(PartyTest, DefaultConstructor) {

   Party p1;

   EXPECT_EQ(p1.getName(), "") << "The name is not correct";

   EXPECT_EQ(p1.getNumVotes(), 0) << "The total votes is not correct";

   EXPECT_EQ(p1.getSeats(), 0) << "The total seats is not correct";

 }

// Checks that DefaultConstructor returns the correct values
TEST_F(PartyTest, ParameterizedConstructor) {

  Party p1("okay");

  EXPECT_EQ(p1.getName(), "okay") << "The name is not correct";

  EXPECT_EQ(p1.getNumVotes(), 0) << "The total votes is not correct";

  EXPECT_EQ(p1.getSeats(), 0) << "The total seats is not correct";

}

// Checks that getNumVotes returns the totak number of Votes
TEST_F(PartyTest, getNumVotes) {

  Party p1;

  p1.addVote();

  EXPECT_EQ(p1.getNumVotes(), 1) << "The total votes is not correct";

  p1.addVote();

  EXPECT_EQ(p1.getNumVotes(), 2) << "The total votes is not correct";

}

// Checks that getSeats returns the totak number of Votes
TEST_F(PartyTest, getSeats) {

  Party p1;

  p1.addSeat(1);

  EXPECT_EQ(p1.getSeats(), 1) << "The total seats is not correct";

  p1.addSeat(1);

  EXPECT_EQ(p1.getSeats(), 2) << "The total seats is not correct";

}

// Checks that getName returns the totak number of Votes
TEST_F(PartyTest, getName) {

  Party p1("alright");

  EXPECT_EQ(p1.getName(), "alright") << "The name is not correct";

  Party p2;

  EXPECT_EQ(p2.getName(), "") << "The name is not correct";

  Party p3("not nice");

  EXPECT_EQ(p3.getName(), "not nice") << "The name is not correct";

}

// Checks that addVote returns the incremented number of Votes
TEST_F(PartyTest, addVote) {

  Party p1;

  p1.addVote();

  EXPECT_EQ(p1.getNumVotes(), 1) << "The total votes is not correct";

  p1.addVote();

  EXPECT_EQ(p1.getNumVotes(), 2) << "The total votes is not correct";

}

// Checks that addSeat returns the icnremented number of seats
TEST_F(PartyTest, AddSetSeat) {

  Party p1;

  p1.addSeat(1);

  EXPECT_EQ(p1.getSeats(), 1) << "The total votes is not correct";

  p1.addSeat(1);

  EXPECT_EQ(p1.getSeats(), 2) << "The total votes is not correct";

  p1.setSeats(3);

  EXPECT_EQ(p1.getSeats(), 3) << "The total votes is not correct";

}

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

  map<string,int> hash_output = election->GetHash();

  EXPECT_EQ(hash_output["D"], 5) << "The Hash is not correct";
  EXPECT_EQ(hash_output["R"], 3) << "The Hash is not correct";

}



TEST_F(Election_TEST, CreateElection){
    Election e;

    string output1 = e.GetType();
    int output2 = e.GetNumBallots();
    string audit = e.GetAuditFile();

    bool output3 = false;
    if (audit.rfind("audit",0) == 0){
        output3 = true;
    }

    ASSERT_EQ(output1, "none");
    ASSERT_EQ(output2, 0);
    ASSERT_EQ(output3, true);
}

TEST_F(Election_TEST, SettersGetters){
    Election e;

    e.SetType("IR");
    e.SetNumBallots(10);

    string output1 = e.GetType();
    int output2 = e.GetNumBallots();

    ASSERT_EQ(output1, "IR");
    ASSERT_EQ(output2, 10);
}

TEST_F(Election_TEST, StringToBallot){
    Election e;

    string ballot = "2,1,4,3 ";
    vector<int> v_ballot = e.ConvertStringBallot(ballot);

    int output1 = v_ballot[0];
    int output2 = v_ballot[1];
    int output3 = v_ballot[2];
    int output4 = v_ballot[3];

    ASSERT_EQ(output1, 2);
    ASSERT_EQ(output2, 1);
    ASSERT_EQ(output3, 4);
    ASSERT_EQ(output4, 3);
}

TEST_F(ELECTION_OFFICIAL_TEST, Constructor){
    ElectionOfficial of1("OPL");
    ElectionOfficial of2("IR");

    EXPECT_EQ(of1.getTypeElection(), "OPL");
    EXPECT_EQ(of2.getTypeElection(), "IR");
}

TEST_F(ELECTION_OFFICIAL_TEST, CreateIR){
    ElectionOfficial eo("eo");
    IR* ir = eo.CreateIRElection("IR.csv");
    string output1 = ir->GetType();

    ASSERT_EQ(output1, "IR");
}

TEST_F(ELECTION_OFFICIAL_TEST, CreateOPL){
    ElectionOfficial eo("eo");
    OPL* opl = eo.CreateOPLElection("OPL.csv");
    string output1 = opl->GetType();

    ASSERT_EQ(output1, "OPL");
}

TEST_F(ELECTION_OFFICIAL_TEST, CreatePO){
    ElectionOfficial eo("eo");
    PO* po = eo.CreatePOElection("PO.csv");
    string output1 = po->GetType();

    ASSERT_EQ(output1, "PO");
}


// Checks that DefaultConstructor works correctly
TEST_F(POTest, DefaultConstructor) {

   PO op;

   EXPECT_EQ(op.GetNumCandidates(), 0) << "The filename is not correct";
   EXPECT_EQ(op.GetType(), "PO") << "The filename is not correct";


   PO op2;

   EXPECT_EQ(op2.GetNumCandidates(), 0) << "The filename is not correct";
   EXPECT_EQ(op.GetType(), "PO") << "The filename is not correct";

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


// check if SetNumCandidates and GetNumCandidates works correctly
TEST_F(POTest, SetGetNumCandidates) {

  PO op;

  op.SetNumCandidates(5);

  EXPECT_EQ(op.GetNumCandidates(), 5) << "The NumCandidates is not correct";

  op.SetNumCandidates(10);

  EXPECT_EQ(op.GetNumCandidates(), 10) << "The NumCandidates is not correct";
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
