#include "gtest/gtest.h"
#include <vector>
#include "../src/ir.h"
#include "../src/candidate.h"
#include "../src/ballot.h"
#include "../src/election.h"
#include <iostream>
#include <map>

using namespace std;

class IR_TEST : public ::testing::Test{
    public:
        void SetUp(){

    }
};

/**********************************************
 * Test Cases
 * *******************************************/

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

TEST_F(IR_TEST, AddBallots){
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
