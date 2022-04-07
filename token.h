// Define our includes
#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>

// Define our namespace
using namespace std;

// Define our tokenID enum
enum tokenID {
	eofTk, 
	errorTk,
	idTk, 
	numTk,
	beginTk, 
	endTk, 
	loopTk, 
	wholeTk, 
	voidTk, 
	exitTk, 
	getterTk, 
	outterTk, 
	mainTk, 
	ifTk, 
	thenTk, 
	assignTk, 
	dataTk, 
	procTk, 
	equalsTk, 
	greatTk, 
	great_eqTk, 
	lessTk, 
	less_eqTk, 
	double_equalsTk,
	colonTk, 
	colon_equalsTk, 
	plusTk, 
	minusTk, 
	asteriskTk, 
	slashTk, 
	modulusTk, 
	periodTk, 
	open_parTk, 
	close_parTk,
	commaTk, 
	open_curlTk, 
	close_curlTk, 
	semicolonTk, 
	open_bracketTk, 
	close_bracketTk
};

// Define our token structure
struct token {
	tokenID tkIdentifier;
	string tkName;
	int lineNum;
};

#endif

