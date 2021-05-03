#include "gtest/gtest.h"
#include "../src/candidate.h"
#include "../src/ballot.h"

class CandidateTest : public ::testing::Test{
    public:
        void SetUp(){

    }
};


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
