#include "gtest/gtest.h"
#include "../src/election.h"
#include <iostream>
#include <map>

using namespace std;

class Election_TEST : public ::testing::Test{
    public:
        void SetUp(){

    }
};

/**********************************************
 * Test Cases
 * *******************************************/

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

    string ballot = "2,1,4,3";
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