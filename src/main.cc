#include <map>
#include <functional>
#include <string>
#include <iostream>
#include "election.h"
#include "election_official.h"
#include "tester.h"
#include <fstream>
#include "ir.h"
#include "opl.h"
#include "party.h"

using namespace std;

int main() {
    string userType;
    string filename;
    string type;
    int numBallots;
    cout << "Welcome to Voting System" << endl;
    // User here
    cout << "Indicate the type of user: Election Official (eo) or Tester (t) " << endl;
    cout << ">> ";
    cin >> userType;
    while (userType != "eo" && userType != "t"){
        cout << "Couldn't recognize type of user" << endl;
        cout << "Indicate the type of user: Election Official (eo) or Tester (t) " << endl;
        cout << ">> ";
        cin >> userType;
    }

    if (userType == "eo"){
        ElectionOfficial of(userType);
        // Commands for election official
        cout << "List of possible commands:" << endl;
        cout << "      help: Get basic information about functionality" << endl;
        cout << "      load: Load Election file and run election" << endl;
        cout << "      quit: Stop the program" << endl;

        cout << endl;
        string input;
        cout << ">> ";
        cin >> input;
        while (input != "quit"){
            if (input == "help"){
                of.help();
            }
            else if (input == "load"){
                of.loadFile();
            }
            else {
                cout << "command \"" << input << "\" not known" << endl;
            }
            cout << ">> ";
            cin >> input;
        }

        cout << endl;
        cout << "Exiting the program" << endl;
        cout << "Thanks for using the Voting System" << endl;
    }
    else if (userType == "t"){
        Tester t;
        cout << "      quit: Stop the program" << endl;


        cout << endl;
        string input;
        cout << ">> ";
        cin >> input;
        while (input != "quit"){
            if (input == "RunIR"){
                t.RunIR();
            }
            else if (input == "RunOPL"){
                t.RunOPL();
            }
            else if (input == "SetOPLFile"){
                t.SetOPLFile();
            }
            else if (input == "SetIRFile"){
                t.SetIRFile();
            }
            else {
                cout << "command \"" << input << "\" not known" << endl;
            }
            cout << ">> ";
            cin >> input;
        }

        cout << endl;
        cout << "Exiting the program" << endl;
        cout << "Thanks for using the Voting System" << endl;
    }

    return 0;
}