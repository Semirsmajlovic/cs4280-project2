// Define our includes
#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "token.h"

// Define lookupChar struct
struct lookupChar {
	char value;
	int key;
};

// Define lookupToken struct
struct lookupToken {
	int key;
	tokenID tkEnum;
};

// Define our scanner prototype
token scanner(ifstream& ifile, int lineNum);

// Define our column search
int findColumn(char nextChar);

// Define our map lookup
token lookup(int value, string searchString);

#endif
