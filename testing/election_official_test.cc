#include "gtest/gtest.h"
#include <vector>
#include "../src/election_official.h"
#include "../src/*.h"
#include <iostream>
#include <map>

using namespace std;

class ELECTION_OFFICIAL_TEST : public ::testing::Test{
    public:
        void SetUp(){

    }
};

/**********************************************
 * Test Cases
 * *******************************************/

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
