/**
 * @file election_official.cc
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */

 #include "election_official.h"
 using namespace std;

 /*******************************************************************************
 * Member Functions
 ******************************************************************************/
ElectionOfficial::ElectionOfficial(string type){
    typeElection = type;
}

void ElectionOfficial::PerformIRElection(string filename){
    cout << "IR file was found" << endl;
    IR* election = CreateIRElection(filename);
    election->WriteToAudit("Type of election: IR\n");
    election->AddBallots(filename);
    election->AddMultipleFiles();
    election->WriteToAudit("Number of votes casted: " + to_string(election->GetNumBallots()) + "\n");
    election->WriteToAudit("Number of valid ballots: " + to_string(election->GetNumValidBallots()) + "\n");
    cout << "Votes have been distributed" << endl;
    cout << "Performing election" << endl;
    election->PerformElection();
}

IR* ElectionOfficial::CreateIRElection(string filename){
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

void ElectionOfficial::PerformOPLElection(string filename){
    cout << "OPL file was found" << endl;
    OPL* election = CreateOPLElection(filename);
    election->WriteToAudit("Type of election: OPL\n");
    election->AddBallots(filename);
    election->AddMultipleFiles();
    election->DistributeSeats();
}

OPL* ElectionOfficial::CreateOPLElection(string filename){
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

void ElectionOfficial::PerformPOElection(string filename){
    cout << "PO file was found" << endl;
    PO* election = CreatePOElection(filename);
    election->AddBallots(filename);
    election->AddMultipleFiles();
    cout << "Number of Candidates in PO election: " << election->GetNumCandidates() << endl;
    cout << "Candidates in PO election are: " << election->GetCandidatesNames() << endl;
    cout << "Number of ballots in PO election: " << election->GetNumBallots() << endl;

}

PO* ElectionOfficial::CreatePOElection(string filename){
    PO* po = new PO();
    string buffer;
    ifstream file (filename);

    getline(file, buffer); // type
    getline(file, buffer); // number of candidates
    po->SetNumCandidates(stoi(buffer));
    getline(file, buffer); // candidates
    po->SetCandidatesNames(buffer);
    po->SetParties(buffer);
    getline(file, buffer); // number of ballots

    file.close();


    return po;
}

string ElectionOfficial::getTypeElection() { return this->typeElection;}

void ElectionOfficial::loadFile() {
    string filename;
    string type;
    cout << "Enter file name" << endl;
    cout << ">> ";
    cin >> filename;
    ifstream file (filename);

    // check if file was opened
    if (file.is_open()){
        // read the file
        // type = 1st line of the file which is the type of election
        string buffer;
        getline(file, type);
        if (type.compare("IR") == 1){
            // Call IR election method to do everything
            file.close();
            PerformIRElection(filename);
        }
        else if (type.compare("PO") == 0){
            // Call OPL election method to do everything
            file.close();
            PerformPOElection(filename);
        }
        else if (type.compare("OPL") == 1){
            // Call OPL election method to do everything
            file.close();
            PerformOPLElection(filename);
        }
        else {
            cout << "Unknown election type" << endl;
        }
    }
    else {
        cout << "File was not found" << endl;
    }
}

 // Function provides help for the user
void ElectionOfficial::help(){
    cout << endl;
    cout << "HELP" << endl;
    cout << "Type \"quit\" to stop the program." << endl;
    cout << endl;
    cout << "Type \"load\" to be prompted for an election file name." << endl;
    cout << "Once an election file has been found, you can obtain the results" << endl;
    cout << "      by typying \"compute\"" << endl;
    cout << endl;
    cout << "Please, visit https://github.umn.edu/umn-csci-5801-S21-001/repo-Team1 for additional help." << endl;
    cout << endl;
}
