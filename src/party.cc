/**
 * @file party.cc
 *
 * @copyright 2021, Spring Semester, CSCI 5801 Student Team 001, All rights reserved.
 */


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

#include "party.h"
using namespace std;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

 Party::Party() {
   nameParty = "";
   numVotes = 0;
   seats = 0;
 }

Party::Party(string n) {
  nameParty = n;
  numVotes = 0;
  seats = 0;
}

 string Party::getName() {
   return nameParty;
 }        //method to get the name of the party

 int Party::getNumVotes() {
   return numVotes;
 }    //method to get the total votes per Party

 int Party::getSeats() {
   return seats;
 }    //method to get the total seats per Party

 void Party::addVote() {
   numVotes++;
 }      //method to add vote to a party

 void Party::setSeats(int a){
   seats = a;
 }

 void Party::addSeat(int s) {
   seats+= s;
   setSeats(seats);
 }       //method to add seat per total votes to a party