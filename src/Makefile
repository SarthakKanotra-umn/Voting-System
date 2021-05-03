# Makefile for Voting System

# *****************************************************
# Variables to control Makefile operation

CC=g++
EXEFILE = main
CFLAGS = -c
SOURCES = election.cc ir.cc main.cc
OBJECTS = $(SOURCES:.cc=.o)
INCLUDES = election.h ir.h

$(EXEFILE): ir.o election.o candidate.o ballot.o opl.o party.o election_official.o PO.o tester.o main.o
	$(CC) -g $^ -o $(EXEFILE)

ir.o: ir.cc
	$(CC) $(CFLAGS) $^

election.o: election.cc
	$(CC) $(CFLAGS) $^

candidate.o: candidate.cc
	$(CC) $(CFLAGS) $^

ballot.o: ballot.cc
	$(CC) $(CFLAGS) $^

opl.o: opl.cc
	$(CC) $(CFLAGS) $^

party.o: party.cc
	$(CC) $(CFLAGS) $^

PO.o: PO.cc
	$(CC) $(CFLAGS) $^

election_official.o: election_official.cc
	$(CC) $(CFLAGS) $^

tester.o: tester.cc
	$(CC) $(CFLAGS) $^

main.o: main.cc
	$(CC) $(CFLAGS) $^

clean:
	$(RM) *.o $(EXEFILE)
