// Define our includes.
#ifndef NODE_H
#define NODE_H
#include "token.h"

// Define our namespace.
using namespace std;

// Node Structure
struct node {

	// Define all of our variables
	string name;
	int level;

	// Define all of our tokens.
	token nToken;
	token nToken2;
	token nToken3;
	token nToken4;
	token nToken5;
		
	// Define all of our nodes.
	node *first_child;
	node *second_child;
	node *third_child;
	node *fourth_child;
};

#endif
