#include "gtest/gtest.h"
#include "../src/ballot.h"


class BallotTest : public ::testing::Test{
    public:
        void SetUp(){

    }
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

TEST(BallotTest, GetVoteTest) {
  std::vector<int> vote{1, 2, 3, 4};
  Ballot b2(vote);

  EXPECT_EQ(b2.GetVote(), vote);
}
