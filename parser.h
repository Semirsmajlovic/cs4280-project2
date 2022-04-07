// Define our includes
#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "node.h"
#include "scanner.h"

// Define our function prototypes
node* program(ifstream& file);
node* vars(ifstream& file);
node* block(ifstream& file);
node* expr(ifstream& file);
node* N(ifstream& file);
node* A(ifstream& file);
node* M(ifstream& file);
node* R(ifstream& file);
node* stats(ifstream& file);
node* mStat(ifstream& file);
node* stat(ifstream& file);
node* in(ifstream& file);
node* out(ifstream& file);
node* if_F(ifstream& file);
node* loop(ifstream& file);
node* assign(ifstream& file);
node* RO(ifstream& file);
node* label(ifstream& file);
node* goto_F(ifstream& file);
node* parser(ifstream& ifile);

#endif
