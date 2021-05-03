/**
 * @file tester.cc
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */

 #include "tester.h"


 using namespace std;

 /*******************************************************************************
 * Member Functions
 ******************************************************************************/

Tester::Tester(){
    cout << "This is the test version of Voting System" << endl;
    cout << "By default, RunIR test uses the file IR.csv" << endl;
    cout << "By default, RunOPL test uses the file OPL.csv" << endl;
    cout << endl;
    cout << "Note: You can change the file for IR and OPL" << endl;
    cout << "using SetIRFile and SetOPLFile. Tests won't match the expected results" << endl;
    cout << "if election files are changed." << endl;

    IRFile = "../testing/IR.csv";
    OPLFile = "../testing/OPL.csv";
    numBallotsIR = 7;
    numBallotsOPL = 9;
}

void Tester::RunOPL(){
    PerformOPLElection(OPLFile);

}

void Tester::RunIR(){
    string type = "IR";
    IR *election = CreateIRElection(IRFile);
    election->SetType(type);
    string electionType = election->GetType();
    cout << "Election type: " << electionType << ". Expected: IR" << endl;
    election->WriteToAudit("Type of election: " + type + "\n");
    election->SetNumBallots(numBallotsIR);
    int ballots = election->GetNumBallots();
    cout << "Number of ballots: " << ballots << ". Expected: 7" << endl;

  
    vector<Candidate> candidates = election->GetCandidates();
    vector<string> names;
    names.push_back("Rosen(D)");
    names.push_back("Kleinberg(R)");
    names.push_back("Chou(I)");
    names.push_back("Royce(L)");
    vector<int> results;
    results.push_back(3);
    results.push_back(0);
    results.push_back(2);
    results.push_back(2);

    for (int i = 0; i < candidates.size(); i++){
        if (i < results.size()){
            cout << "Candidate: " << candidates.at(i).GetName() << ". Expected: " << names.at(i) << endl;
            candidates.at(i).SetTotalVotes(results[i]);
            cout << "Received: " << candidates.at(i).TotalVotes() << " votes. Expected: " << results.at(i) << " votes" << endl;
        }
    }
    PerformIRElection(IRFile);
}

void Tester::SetOPLFile(){
    string filename;
    cin >> filename;
    ifstream file (filename);
    if (file.is_open()){
        OPLFile = filename;
        string type;
        getline(file, type);
        if (type.compare("OPL") == 1 || type.compare("OPL") == 0){
            string buffer;
            file.ignore(1,'\n');
            file.ignore(1000,'\n');
            file.ignore(1000,'\n');
            file.ignore(1000,'\n');
            getline(file, buffer);
            numBallotsOPL = stoi(buffer);
            
            file.close();
        }
    }
    else {
        cout << "File was not found" << endl;
    }

}

void Tester::SetIRFile(){
    cout << "Use file 'IR.csv' to validate election properly." << endl;
    string filename;
    cin >> filename;
    ifstream file (filename);
    if (file.is_open()){
        IRFile = filename;
        string type;
        getline(file, type);
        if (type.compare("IR") == 1 || type.compare("IR") == 0){
            string buffer;
            file.ignore(1,'\n');
            file.ignore(1000,'\n');
            file.ignore(1000,'\n');
            getline(file, buffer);
            numBallotsIR = stoi(buffer);

            file.close();
        }
    }
    else {
        cout << "File was not found" << endl;
    }
}

void Tester::PerformIRElection(string filename) {
    cout << "IR file was found" << endl;
    IR* election = CreateIRElection(filename);
    election->WriteToAudit("Type of election: IR\n");
    election->AddBallots(filename);
    election->AddMultipleFiles();
    election->WriteToAudit("Number of votes casted: " + to_string(election->GetNumBallots()) + "\n");
    cout << "Votes have been distributed" << endl;
    cout << "Performing election" << endl;
    election->PerformElection();
    cout << "Expected winner: Rosen(D). Winner: " << election->GetWinner() << endl;

}

IR* Tester::CreateIRElection(string filename) {
    IR* ir = new IR();
    string buffer;
    ifstream file (filename);

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    ir->WriteToAudit("Number of candidates: " + buffer + "\n");
    getline(file, buffer); // candidates
    ir->SetCandidates(buffer);
    getline(file, buffer); // number of ballots

    file.close();

    return ir;
}

void Tester::PerformOPLElection(string filename){
    cout << "OPL file was found" << endl;
    OPL* election = CreateOPLElection(filename);
    
    election->SetType("OPL");
    string electionType = election->GetType();
    cout << "Election type: " << electionType << ". Expected: OPL" << endl;

    election->WriteToAudit("Type of election: OPL\n");
    election->AddBallots(filename);
    int ballots = election->GetNumBallots();
    cout << "Number of ballots: " << ballots << ". Expected: 9" << endl;
    election->AddMultipleFiles();
    election->DistributeSeats();
}

OPL* Tester::CreateOPLElection(string filename){
    OPL* opl = new OPL();
    string buffer;
    ifstream file (filename);

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    opl->WriteToAudit("Number of candidates: " + buffer + "\n");
    opl->SetNumCandidates(stoi(buffer));
    getline(file, buffer); // candidates
    opl->SetCandidatesNames(buffer);
    opl->WriteToAudit("Candidates are " + opl->GetCandidatesNames() + "\n");
    opl->SetParties(buffer);
    getline(file, buffer); // number of seats
    opl->SetSeats(stoi(buffer));
    opl->WriteToAudit("Number of Seats: " + buffer + '\n');
    getline(file, buffer);

    file.close();


    return opl;
}