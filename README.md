# repo-Team1
Team1 (Alene, Leal, Oberstar, Kanotra)

## Introduction

Welcome to the Voting System.

The voting system developed performs two types of elections:

* Open Party Listing.
* Instant Runoff Voting.


### Open Party Listing

Legislators are elected in large, multi-member districts. Each party puts up a list of candidates equal
to the number of seats in the district. Independent candidates may also run, and they are listed separately
on the ballot as if they were their own party. On the ballot, voters indicate their preference for a particular
party and the parties then receive seats in proportion to their share of the vote. So in a five-member district,
if the Democrats win 40% of the vote, they would win two of the five seats. The two winning Democratic candidates
would be chosen according to their position on the list.

### Instant Runoff Voting

Instant runoff voting, also known as "IRV", is very similar to plurality voting where every single
candidate is listed on the ballot. In this election, voters rank the candidates in the order of
their preference. The counting of the ballot, however, is different from plurality voting. The Votes
for all the candidates marked down as the first ("1") preference are counted and a majority of over
50% is checked for. Following this, if a clear winner does not exist, the candidate with the fewest
votes is eliminated and the ballots of the supporters of this candidate are transferred to whichever
of the remaining candidates they marked as their second ("2") choice. This process carries on till a clear
winner is found. In case of a tie, the winning candidate is chosen by a randomized series of coin tosses.

### Audit File

For either of the aforementioned elections, an audit file will be produced at the end of the election.
This file contains all the necessary information, results, and data related to the election in order to
verify and maintain the integrity of the election.

In addition to this, the winner will also be displayed to the screen on terminal.


## Documentation 

To generate documentation, first build the project with `make` in the `project` directory.
Next, navigate to `project/documentation` and run `doxygen Doxyfile`.
Then open `project/documentation/html/index.html` in your web browser to view the documentation.

* ON TERMINAL: 
    * $ cd Project1
    * $ cd documentation
    * $ doxygen Doxyfile
    * Navigate to the html folder and view documentation on your browser by clicking on `index.html`.

## How To Run The Voting System

To run the voting system, the user must be in the correct directory:

* ON TERMINAL: $ cd umn-csci-5801-s21-001/repo-Team001

Then, on terminal, change directory into `Project1` and then into `src`:

* ON TERMINAL: 
    * $ cd Project1
    * $ cd src

Run the command: `make` on terminal in the src directory.

Following this, run the command: `./main`.

* ON TERMINAL: 
    * $ make
    * $ ./main

You will be prompted with options to guide the user through it:

* ">> help" will show the user how to load the election file in the system
which must be in the same directory - Project1/src/<your-file.csv>

* ">> load" will prompt the user to enter the election filename - <filename.csv>. Once a valid election file has been found, the system will
promp the user if they want to add more election files to the election. The user can type y (yes) or n (no). Once the user decides that they don't want to add more files by entering n (no) to the prompt, the system will compute the results of the election, displaying the results to the screen and creating an audit file.

* ">> quit" will exit out of the voting system.

Run the command `make clean` - ($ make clean) on terminal to clean all
executable files and repeat the process to re-run the Voting System.

## How To Run Tests As a Tester In The Voting System

### Run Google Unit Tests

To run the google tests the user must follow these steps:
 ON TERMINAL: $ cd umn-csci-5801-s21-001/repo-Team001

On the terminal change directory to Project1 and then testing.

* ON TERMINAL: 
    * $ cd Project1
    * $ cd testing

Once in the testing directory you can run any of the test files.

To run google tests use the following command:

* On TERMINAL: 
    * $ make
    * $ ./testing

This will display the google unit tests on the terminal itself. 

### Verify Election Results

To verify the election itself, the tester can do the following: 

* ON TERMINAL: 
    * $ cd Project1
    * $ cd src
    * $ make
    * $ ./main
    * $ >> t
    * (NOTE: To run IR election with the provided test file `IR.csv`):
    * $ RunIR 
    (NOTE: To run OPL election with the provided test file `OPL.csv`):
    * $ RunOPL 
    * (NOTE: To run OPL with the your own test file (Expected results may differ)):
    * $ SetOPLFile
    * `<your-filename.csv>`
    * $ RunOPL
    * (NOTE: To run IR with the your own test file (Expected results may differ)):
    * $ SetIRFile
    * `<your-filename.csv>`
    * $ RunIR

This will display the election information to the screen. 

Thank you for choosing to run the Voting System.
