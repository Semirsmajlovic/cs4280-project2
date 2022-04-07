// Define includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "scanner.h"

// Define our namespace
using namespace std;

// Define our FSA table
int FSATable[26][24] = {
	{   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,   -1},
	{1000,    1,    1, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000},
	{1001, 1001,    2, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
	{1002, 1002, 1002,   22,   23,   24, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002},
	{1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005},
	{   9,    9,    9, 1002, 1004, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002},
	{1000,    1,    1, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000},
	{1008, 1008, 1008,   25, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008, 1008},
	{1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010, 1010},
	{1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011, 1011},
	{1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012, 1012},
	{1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013},
	{1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014, 1014},
	{1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015, 1015},
	{1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016, 1016},
	{1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017},
	{1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018},
	{1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019},
	{1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020},
	{1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021, 1021},
	{1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022},
	{1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023},
	{1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007},
	{1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006},
	{1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004},
	{1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009},
};

// List of characters
lookupChar finalCharLookup[] = {
	{'=', 3}, 
	{'<', 4}, 
	{'>', 5}, 
	{'_', 6}, 
	{':', 7}, 
	{'+', 8},
	{'-', 9}, 
	{'*', 10}, 
	{'/', 11}, 
	{'%', 12}, 
	{'.', 13},
	{'(', 14},
	{')', 15},
	{',', 16},
	{'{', 17},
	{'}', 18},
	{';', 19},
	{'[', 20},
	{']', 21}
};

// List of tokens and corresponding final state
lookupToken finalTokenLookup[] = {
	{-1, eofTk},
	{-2, errorTk}, 
	{1000, idTk}, 
	{1001, numTk}, 
	{1002, equalsTk}, 
	{1003, greatTk}, 
	{1004, great_eqTk},
	{1005, lessTk}, 
	{1006, less_eqTk}, 
	{1007, double_equalsTk}, 
	{1008, colonTk}, 
	{1009, colon_equalsTk},
	{1010, plusTk}, 
	{1011, minusTk}, 
	{1012, asteriskTk}, 
	{1013, slashTk}, 
	{1014, modulusTk}, 
	{1015, periodTk},
	{1016, open_parTk}, 
	{1017, close_parTk}, 
	{1018, commaTk}, 
	{1019, open_curlTk}, 
	{1020, close_curlTk},
	{1021, semicolonTk}, 
	{1022, open_bracketTk}, 
	{1023, close_bracketTk}
};

// List of reserved keywords
token finalKeywordLookup[] = {
	{beginTk, "begin", 0}, 
	{endTk, "end", 0}, 
	{loopTk, "loop", 0}, 
	{wholeTk, "whole", 0},
	{voidTk, "void", 0}, 
	{exitTk, "exit", 0}, 
	{getterTk, "getter", 0}, 
	{outterTk, "outter", 0}, 
	{mainTk, "main", 0}, 
	{ifTk, "if", 0}, 
	{thenTk, "then", 0}, 
	{assignTk, "assign", 0}, 
	{dataTk, "data", 0}, 
	{procTk, "proc", 0}
};

// Define our token scanner
token scanner(ifstream& ifile, int lineN) {
	token returnTk;
	static int lineNum = lineN;
	char currChar;
	char nextChar;
	int stateColumn;
	int currentState = 0;
	int nextState = 0;
	string tkString;

	while (currentState < 1000 && currentState >= 0) {
		ifile.get(currChar);
		if(ifile.eof()) {
			returnTk.tkIdentifier = eofTk;
			returnTk.lineNum = lineNum;
			returnTk.tkName = "EOF";
			
			return returnTk;
		}
		if (currChar == '$') {
			int line = lineNum;
			ifile.get(currChar);
			ifile.get(currChar);
			ifile.get(nextChar);
			while (currChar != '$' && nextChar != '$') {
				currChar = nextChar;
				ifile.get(nextChar);
				if (ifile.eof()) {
					cout << "Error: Our comment was started at line " << line << " but never closed\n";
					returnTk.tkIdentifier = errorTk;
					returnTk.lineNum = line;
					returnTk.tkName = "Error";
					exit(1);
				}
				if (nextChar == '\n') {
					lineNum++;
				}
			}
			ifile.get(currChar);
			ifile.get(currChar);
		}
		stateColumn = findColumn(currChar);
		nextState = FSATable[currentState][stateColumn];	
		if (stateColumn == -2) {
			cout << "Error: We have an error at line " << lineNum << " for the reason: invalid character: " << currChar << "\n";
			returnTk.tkIdentifier = errorTk;
			returnTk.lineNum = lineNum;
			returnTk.tkName = currChar;
			exit(1);
		}
	
		if (nextState >= 1000 || nextState == -1) {
			if (nextState == -1) {
				returnTk.tkIdentifier = eofTk;
				returnTk.lineNum = lineNum;
				returnTk.tkName = "EOF";

				return returnTk;
			}
			else if (nextState == 1004 || nextState == 1006 || nextState == 1007 || nextState == 1009) {
				returnTk = lookup(nextState, tkString);
				returnTk.lineNum = lineNum;
				ifile.unget();
				
				return returnTk;
			}
			else if (nextState == 1004 || nextState == 1006) {
				returnTk = lookup(nextState, tkString);
				returnTk.lineNum = lineNum;
				ifile.unget();
				ifile.unget();

				return returnTk;
			}
			else if (nextState >= 1000) {
				returnTk = lookup(nextState, tkString);
				returnTk.lineNum = lineNum;
				ifile.unget();
				if (nextState == 1000) {
					 if(tkString[0] != '_' && tkString[0] == toupper(tkString[0])) {
						cout << "Error: We have an invalid character identifier " << tkString << " at line " << lineNum << "\n";
						cout << "Error: Identifiers must not begin with capital letters.\n";
						
						exit(1);
					}
				}

				return returnTk;
			}
		} else {
			char value = currChar;
			if (!isspace(value)) {
				tkString += value;
			}			
			if (tkString.length() > 8) {
				cout << "Error: We have an issue at line: " << lineNum << "\n";
				returnTk.tkIdentifier = errorTk;
				returnTk.lineNum = lineNum;
				returnTk.tkName = "Error";
				exit(1);
			}
			if (currChar == '\n') {
				lineNum++;
			}
			currentState = nextState;
		}
	}
		
	// Catch scanner failure
	returnTk.tkIdentifier = errorTk;
	returnTk.lineNum = lineNum;
	returnTk.tkName = "Error: The scanner has failed, we are not terminating.. \n";
	cout << "Error: The scanner has failed, we are not terminating..\n";

	exit(1);
}

// Search for our column in the FSA table
int findColumn(char nextChar) {
	if (isalpha(nextChar)) {
		return 1;
	}
	else if (isdigit(nextChar)) {
		return 2;
	}
	else if (isspace(nextChar)) {
		return 0;
	}
	else if (nextChar == EOF) {
		return 22;
	}
	else if (nextChar != EOF || !isalpha(nextChar) || !isdigit(nextChar) || !isspace(nextChar)) {
		for (int i = 0 ; i < (sizeof(finalCharLookup)/sizeof(finalCharLookup[0])) ; i++) {
			if (finalCharLookup[i].value == nextChar) {
				return finalCharLookup[i].key;
			}
		}
	}
	
	return -2;
}

// Define our lookup token
token lookup(int value, string searchString) {
	token returnTk;
	for (int i = 0 ; i < (sizeof(finalTokenLookup)/sizeof(finalTokenLookup[0])) ; i++) {
		if (finalTokenLookup[i].key == value) {
			returnTk.tkIdentifier = finalTokenLookup[i].tkEnum;
			returnTk.tkName = searchString;
			returnTk.lineNum = 999;
		}
	}
	if (value == 1000) {
		for (int j = 0 ; j < (sizeof(finalKeywordLookup)/sizeof(finalKeywordLookup[0])) ; j++) {
			if (finalKeywordLookup[j].tkName == searchString) {
				returnTk.tkIdentifier = finalKeywordLookup[j].tkIdentifier;
				returnTk.tkName = finalKeywordLookup[j].tkName;
				returnTk.lineNum = 999;
			}
			
		}
			
	}

	return returnTk;
}
