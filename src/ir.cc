#include "ir.h"
#include "election.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <math.h>

using namespace std;

// Get the index where an integer "key" is found
// Use to redistribute ballots
int GetIndexBallot(vector<int> ballot, int key){
    std::vector<int>::iterator itr = std::find(ballot.begin(), ballot.end(), key);
    if (itr != ballot.end()){
        return distance(ballot.begin(), itr);
    }
    // rank not found
    return -1;
}

// Create hash table to know how many current votes a candidate has
// Use in PerformElection to help find a winner
map<string, int> CreateHashTable(vector<Candidate> candidates){
    map<string, int> hash;
    for (Candidate candidate : candidates){
        hash[candidate.GetName()] = candidate.TotalVotes();
    }
    return hash;
}

IR::IR(){
    numValidBallots = 0;
    numCandidates = 0;
    winner = "None";
    SetType("IR");
}

vector<Candidate> IR::GetCandidates(){
    return candidates;
}

int IR::SolveTie(int n){
    int randInt;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++){
        randInt = rand() % n;
    }

    return randInt;
}

void IR::SetCandidate(Candidate candidate){
    candidates.push_back(candidate);
}

string IR::GetWinner(){
    return winner;
}

void IR::SetWinner(string candidate){
    winner = candidate;
}

bool IR::CheckWinner(map<string, int> &m){
    int count = 0;
    std::map<string, int>::iterator itr;
    for (itr=m.begin(); itr!=m.end(); itr++){
        // A candidate has 50% of the votes
        if (((float) itr->second / (float) GetNumValidBallots()) >= 0.5){
            SetWinner(itr->first);
            float result = ((float) itr->second / (float) GetNumValidBallots()) * 100;
            int result_int  = (int) result;
            WriteToAudit("Candidate " + itr->first + " wins with " + to_string(result)
            + "% of the votes\n");
            return true;
        }
        else if (itr->second > 0){
            count++;
        }
    }
    return count==2;
}

void IR::PerformElection(){
    map<string, int> m = CreateHashTable(candidates);
    map<string, int>::iterator itr;
    
    // Loop until a winner is found
    // If no winner is found, find loser and redistribute votes
    while (!CheckWinner(m)){
        WriteToAudit("Current vote distribution:\n");
        for (itr=m.begin(); itr!=m.end();++itr){
            WriteToAudit(itr->first + " " + to_string(itr->second) + " votes\n");
        }
        // Find losing candidate/s
        int minBallots = numeric_limits<int>::max();
        vector<int> losingCandidateIdx;
        for (int i = 0; i < candidates.size(); i++){
            if (candidates.at(i).TotalVotes() < minBallots && candidates.at(i).TotalVotes() > 0){
                minBallots = candidates.at(i).TotalVotes();
                losingCandidateIdx.clear();
                losingCandidateIdx.push_back(i);
            }
            else if (candidates.at(i).TotalVotes() == minBallots && candidates.at(i).TotalVotes() > 0){
                losingCandidateIdx.push_back(i);
            }
        }

        // Check how many losing candidates were found
        // One losing candidate
        if (losingCandidateIdx.size() == 1){
            int idx = losingCandidateIdx.at(0);
            WriteToAudit("\nCandidate " + candidates.at(idx).GetName() + " lost the election\n");
            WriteToAudit("His/Her votes are being distributed\n");
            RedistributeBallots(idx);
        }
        // Multiple losing candidates
        else {
            int numCandidates = losingCandidateIdx.size();
            int idx = SolveTie(numCandidates);
            int idx_candidate = losingCandidateIdx.at(idx);
            WriteToAudit("\nCandidate " + candidates.at(idx_candidate).GetName() + " lost the election\n");
            WriteToAudit("His/Her votes are being distributed\n");
            RedistributeBallots(idx_candidate);
        }
        m = CreateHashTable(candidates);
    }

    // Winner found
    int count = 0;
    int idxWinner = 0;
    int max = -1;
    string winner;
    for (itr=m.begin(); itr!=m.end(); itr++){
        if (itr->second > max){
            max = itr->second;
            idxWinner=count;
            winner = itr->first;
        }
        else if (itr->second == max){
            int idx = SolveTie(2);
            if (idx == 1){
                idxWinner=count;
                winner = itr->first;
            }
        }
        count++;
    }
    SetWinner(winner);
    WriteToAudit("\n" + winner + " won the election\n");
    WriteToAudit("Final Results:\n");
    for (Candidate c : candidates){
        float result = (float) c.TotalVotes() / (float) GetNumBallots();
        int resultInt = (int) result;
        WriteToAudit(c.GetName() + " " + to_string(result) + "% ");
    }
    cout << "Winner is: " << winner << endl;
}

void IR::RedistributeBallots(int candidateIdx){
    vector<Ballot> ballots;
    for (int i = 0; i<candidates.at(candidateIdx).GetVotes().size(); i++){
        Ballot ballot = candidates.at(candidateIdx).GetVotes().at(i);
        ballot.IncrementRank();
        ballots.push_back(ballot);
    }
    candidates.at(candidateIdx).SetVotes(ballots);

    for (Ballot b : candidates.at(candidateIdx).GetVotes()){
        vector<int> vote = b.GetVote();
        bool foundCandidate = false;
        while (!foundCandidate){
            int idx = GetIndexBallot(vote, b.GetRank());
            // need to move the ballot
            if (idx < 0){
                foundCandidate = true;
            }
            else if (b.GetRank()>1 && idx>=0 && candidates.at(idx).GetVotes().size()!=0){
                WriteToAudit("Ballot with ID" + to_string(b.GetId()));
                WriteToAudit(" is being reallocated to " + candidates.at(idx).GetName() + "\n");
                vector<Ballot> new_ballots = candidates.at(idx).GetVotes();
                new_ballots.push_back(b);
                candidates.at(idx).SetVotes(new_ballots);
                candidates.at(idx).IncrementCount();
                foundCandidate = true;
            }
            else {
                b.IncrementRank();
            }
        }
    }
    candidates.at(candidateIdx).SetCountToZero();
    ballots.clear();
    candidates.at(candidateIdx).SetVotes(ballots);
}

void IR::SetCandidates(string stream){
    stringstream s_stream(stream);
    while(s_stream.good()) {
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        substr.erase(std::remove_if(substr.begin(), substr.end(), ::isspace), substr.end());
        Candidate candidate(substr);
        candidates.push_back(candidate);
    }

    for (Candidate c : candidates){
        WriteToAudit(c.GetName() + " ");
    }
    WriteToAudit("\n");
}

void IR::SetNumValidBallots(int n){
    numValidBallots += n;
}

int IR::GetNumValidBallots(){
    return numValidBallots;
}

bool IR::IsValidBallot(vector<int> ballot){
    int count = 0;
    for (int i = 0; i < ballot.size(); i++){
        if (ballot.at(i) > 0){
            count++;
        }
    }
    return count>=ceil((float)ballot.size()/2);
}

void IR::AddBallots(string electionFile){
    ifstream file (electionFile);
    if (file.is_open()){
        string buffer;
        getline(file, buffer); // type
        getline(file, buffer); // number of candidates
        getline(file, buffer); // candidates
        getline(file, buffer); // number of ballots
        SetNumBallots(stoi(buffer));

        while (getline(file, buffer)){
            vector<int> ballot = ConvertStringBallot(buffer);
            if (IsValidBallot(ballot)){
                SetNumValidBallots(1);
                Ballot new_ballot(ballot);
                int min_val = ballot.size()+1;
                for (int i = 0; i < ballot.size(); i++){
                    if (ballot.at(i) > 0 && ballot.at(i) < min_val){
                        min_val = ballot.at(i);
                    }
                }
                new_ballot.SetRank(min_val);
                int idx = GetIndexBallot(ballot, min_val);
                candidates.at(idx).AddVote(new_ballot);
            }
        }
    }
    else {
        cout << "File not found" << endl;
    }
}

void IR::AddMultipleFiles(){
    string answer;
    cout << "   Would you like to add another file to this election? (y/n)" << endl;
    cout << ">> ";
    cin >> answer;

    while (answer.compare("y") == 0){
        string filename;
        cout << "   Enter file name" << endl;
        cout << ">> ";
        cin >> filename;
        AddBallots(filename);

        cout << "   Would you like to add another file to this election? (y/n)" << endl;
        cout << ">> ";
        cin >> answer;
    }

    WriteToAudit("\n");
    for (Candidate c : candidates){
        string name = c.GetName();
        int votes = c.GetVotes().size();
        string strVotes = to_string(votes);
        float votes_p = (float) c.TotalVotes() / (float) GetNumBallots();
        int resultInt = (int) votes_p;
        WriteToAudit("Candidate " + name + " received " + strVotes + " vote/s " + to_string(votes_p) + "%\n");
    }
    WriteToAudit("\n\n");
}
