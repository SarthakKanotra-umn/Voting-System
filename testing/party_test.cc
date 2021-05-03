#include "gtest/gtest.h"
#include "../src/party.h"


#include<math.h>
#include<assert.h>
#include <iostream>
#include <string>

using namespace std;



class PartyTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
  virtual void TearDown() {}


};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

// Checks that DefaultConstructor works correctly
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