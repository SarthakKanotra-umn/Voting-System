#include "election.h"
#include <ctime>

using namespace std;

Election::Election(){
    type = "none";
    numBallots = 0;

    // current date/time based on current system
    time_t now = time(0);

    tm *ltm = localtime(&now);

    // print various components of tm structure.
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int hour = ltm->tm_hour;
    int min = ltm->tm_min;
    int sec = ltm->tm_sec;

    string day_string;
    string month_string;

    if (day < 10){
       day_string = "0" + to_string(day);
    }
    else {
        day_string = to_string(day);
    }

    if (month < 10){
       month_string = "0" + to_string(month);
    }
    else {
        month_string = to_string(month);
    }



    auditFile = "audit_" + month_string + day_string + to_string(year)
                + "_" + to_string(hour) + to_string(min) + to_string(sec) + ".csv";
}

void Election::SetNumBallots(int n){
    numBallots += n;
}

void Election::SetType(string t){
    type = t;
}

string Election::GetType(){
    return type;
}

int Election::GetNumBallots(){
    return numBallots;
}

string Election::GetAuditFile(){
    return auditFile;
}

void Election::AddNewBallots(int newBallots){
    numBallots+=newBallots;
}

vector<int> Election::ConvertStringBallot(string ballot){

    vector<int> ballotVector;
    ballot.pop_back();

    for (int i = 0; i < ballot.length(); i++){
        if (i==0 && ballot.at(i)==','){
            ballotVector.push_back(0);
        }
        else if (i > 0 && ballot.at(i-1)==',' && ballot.at(i)==','){
            ballotVector.push_back(0);
        }
        else if (i == ballot.length()-1 && ballot.at(i)==','){
            ballotVector.push_back(0);
        }
        else if (ballot.at(i) != ','){
            ballotVector.push_back((int)ballot.at(i)-48);
        }
    }
    
    return ballotVector;
}

void Election::WriteToAudit(string s){
    string filename = GetAuditFile();
    ofstream file;
    file.open(filename, ofstream::out | ofstream::app);
    file << s;
    file.close();
}