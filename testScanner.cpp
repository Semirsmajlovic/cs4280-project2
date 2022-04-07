// Define our includes
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "testScanner.h"
#include "scanner.h"

// Define our namespace
using namespace std;

// Token names to output
string token_names[] = {
	"End of File",
	"Error",
	"Identifier",
	"Integer",
	"Begin Keyword",
	"End Keyword",
	"Loop Keyword",
	"Whole Keyword",
	"Void Keyword",
	"Exit Keyword",
	"Getter Keyword",
	"Outter Keyword",
	"Main Keyword",
	"If Keyword",
	"Then Keyword",
	"Assign Keyword",
	"Data Keyword",
	"Proc Keyword",
	"Equals Sign",
	"Greater Sign",
	"Greater Equal",
	"Less Sign",
	"Less Equal",
	"Double Equal",
	"Colon",
	"Colon Equal",
	"Plus Sign",
	"Minus Sign",
	"Asterisk",
	"Slash",
	"Modulus",
	"Period",
	"Open Parenthesis",
	"Close Parenthesis",
	"Comma",
	"Open Curly",
	"Close Curly",
	"Semicolon",
	"Open Bracket",
	"Close Bracket"
};

// Define our driver for the scanner
void testScanner(ifstream& ifile) {
	token tk;
	int lineNum = 1;
	while (ifile) {
		tk = scanner(ifile, lineNum);
		if (token_names[tk.tkIdentifier] == "Identifier" && isalpha(tk.tkName[0])) {
			if (tk.tkName[0] == toupper(tk.tkName[0])) {
				cout << "SCANNER ERROR: invalid identifier " << tk.tkName << " at line " << tk.lineNum << "\n";
				cout << "Identifiers cannot begin with a capital letter\n";

				return;
			}
		}
		if (token_names[tk.tkIdentifier] == "Error") {
			return;
		}
		else {
			cout << "| Our Token ID: " << token_names[tk.tkIdentifier] << ", Current Instance: " 
				<< tk.tkName << ", Defined at Line: " << tk.lineNum << " |\n";
		}
	}

	return;
}
