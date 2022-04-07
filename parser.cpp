// Define our includes
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "parser.h"

// Name our variables
int level = 0;
int lineNum = 1;
token tk;

// List of token names.
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

// Create new new node
node* getNode(string n) {
	node *newNode = new node;
	newNode->name = n;
	newNode->level = level;
	newNode->first_child = NULL;
	newNode->second_child = NULL;
	newNode->third_child = NULL;
	newNode->fourth_child = NULL;
	
	return newNode;
}

// Program node defined
node* program(ifstream& file) {
	
	// We have a program node.
	cout << "\nThe output is: \n\n";
	node *newNode = getNode("<program>");
	level++;
	newNode->first_child = vars(file);
	
	// Match our token identifier with main token
	if (tk.tkIdentifier == mainTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->second_child = block(file);

		return newNode;
	} else {
		cout << "Error: We have an invalid token provided - Expected main keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Vars node defined.
node* vars(ifstream& file) {
	node *newNode = getNode("<vars>");

	// Start if statement rundown.
	if (tk.tkIdentifier == dataTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		
		if (tk.tkIdentifier == idTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);

			if (tk.tkIdentifier == colon_equalsTk) {
				newNode->nToken3 = tk;
				tk = scanner(file, lineNum);
			
				if (tk.tkIdentifier == numTk) {
					newNode->nToken4 = tk;
					tk = scanner(file, lineNum);
					
					if (tk.tkIdentifier == semicolonTk) {
						newNode->nToken5 = tk;
						tk = scanner(file, lineNum);
						level++;
						newNode->first_child = vars(file);
						return newNode;
					} else {
						cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
						exit(1);
					}
				} else {
					cout << "Error: We have an invalid token provided - Expected integer but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
					exit(1);
				}
			} else {
				cout << "Error: We have an invalid token provided - Expected colon equals but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
				exit(1);
			}
		} else {
			cout << "Error: We have an invalid token provided - Expected identifier but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		return NULL;
	}
}

// Block node defined.
node* block(ifstream& file) {
	node *newNode = getNode("<block>");

	// Check if we have a beginning token as token identifier
	if (tk.tkIdentifier == beginTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		level++;
		newNode->first_child = vars(file);
		newNode->second_child = stats(file);

		// Check if we have a ending token as token identifier
		if (tk.tkIdentifier == endTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);
			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected end keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		cout << "Error: We have an invalid token provided - Expected beginning keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Expr node defined
node* expr(ifstream& file) {
	level++;
	node *newNode = getNode("<expr>");
	newNode->first_child = N(file);

	// Check if we have a minus token as token identifier
	if (tk.tkIdentifier == minusTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->second_child = expr(file);

		return newNode;
	} else {
		return newNode;
	}
}

// Define our N node
node* N(ifstream& file) {
	level++;
	node *newNode = getNode("<N>");

	newNode->first_child = A(file);

	if (tk.tkIdentifier == slashTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->second_child = N(file);

		return newNode;
	} else if (tk.tkIdentifier == asteriskTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->second_child = N(file);

		return newNode;
	} else {
		return newNode;
	}
}

// Define our A node
node* A(ifstream& file) {
	level++;
	node *newNode = getNode("<A>");

	newNode->first_child = M(file);

	if (tk.tkIdentifier == plusTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->second_child = A(file);

		return newNode;
	} else {
		return newNode;
	}
}

// Define our M node
node* M(ifstream& file) {
	level++;
	node *newNode = getNode("<M>");

	if (tk.tkIdentifier == asteriskTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->first_child = M(file);

		return newNode;
	} else {
		newNode->first_child = R(file);
		return newNode;
	}
}

// Define our R node
node* R(ifstream& file) {
	level++;
	node *newNode = getNode("<R>");

	if (tk.tkIdentifier == open_parTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->first_child = expr(file);

		if (tk.tkIdentifier == close_parTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);
			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected closing parenthesis but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else if (tk.tkIdentifier == idTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);

		return newNode;
	} else if (tk.tkIdentifier == numTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);

		return newNode;
	} else {
		cout << "Error: We have an invalid token provided - Expected opening paranthesis but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Define our stats node
node* stats(ifstream& file) {
	level++;
	node *newNode = getNode("<stats>");
	
	newNode->first_child = stat(file);
	newNode->second_child = mStat(file);

	return newNode;
}

// Define our mStat node
node* mStat(ifstream& file) {
	if (tk.tkIdentifier == getterTk || 
		tk.tkIdentifier == outterTk || 
		tk.tkIdentifier == beginTk || 
		tk.tkIdentifier == ifTk || 
		tk.tkIdentifier == loopTk ||
		tk.tkIdentifier == assignTk || 
		tk.tkIdentifier == procTk || 
		tk.tkIdentifier == voidTk) {
		level++;
		node *newNode = getNode("<mStat>");
		newNode->first_child = stat(file);
		newNode->second_child = mStat(file);

		return newNode;
	} else {
		return NULL;
	}
}

// Define our stat node.
node* stat(ifstream& file) {
	level++;
	node *newNode = getNode("<stat>");
	
	if (tk.tkIdentifier == getterTk) {
		newNode->first_child = in(file);
		if (tk.tkIdentifier == semicolonTk) {
			newNode->nToken = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else if(tk.tkIdentifier == outterTk) {
		newNode->first_child = out(file);
		if (tk.tkIdentifier == semicolonTk) {
			newNode->nToken = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else if (tk.tkIdentifier == beginTk) {
		newNode->first_child = block(file);
		return newNode;
	} else if (tk.tkIdentifier == ifTk) {
		newNode->first_child = if_F(file);
		if (tk.tkIdentifier == semicolonTk) {
			newNode->nToken = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else if (tk.tkIdentifier == loopTk) {
		newNode->first_child = loop(file);
		if (tk.tkIdentifier == semicolonTk) {
			newNode->nToken = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else if (tk.tkIdentifier == assignTk) {
		newNode->first_child = assign(file);
		if(tk.tkIdentifier == semicolonTk) {
			newNode->nToken = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else if (tk.tkIdentifier == procTk) {
		newNode->first_child = goto_F(file);
		if (tk.tkIdentifier == semicolonTk) {
			newNode->nToken = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else if (tk.tkIdentifier == voidTk) {
		newNode->first_child = label(file);
		if (tk.tkIdentifier == semicolonTk) {
			newNode->nToken = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected semicolon but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		cout << "We have an parse error, please try again.";
		exit(1);
	}
}

// Define our in node
node* in(ifstream& file) {
	level++;
	node *newNode = getNode("<in>");
	if (tk.tkIdentifier == getterTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		if (tk.tkIdentifier == idTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected identifier but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		cout << "Error: We have an invalid token provided - Expected getter keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Define our out node
node* out(ifstream& file) {
	level++;
	node *newNode = getNode("<out>");

	if (tk.tkIdentifier == outterTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		newNode->first_child = expr(file);

		return newNode;
	} else {
		cout << "Error: We have an invalid token provided - Expected outer keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Define our if_F node
node* if_F(ifstream& file) {
	if (tk.tkIdentifier == ifTk) {
		level++;
		node *newNode = getNode("<if>");
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		
		if (tk.tkIdentifier == open_bracketTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);
			newNode->first_child = expr(file);
			newNode->second_child = RO(file);
			newNode->third_child = expr(file);

			if (tk.tkIdentifier == close_bracketTk) {
				newNode->nToken3 = tk;
				tk = scanner(file, lineNum);
				
				if (tk.tkIdentifier == thenTk) {
					newNode->nToken4 = tk;
					tk = scanner(file, lineNum);
					newNode->fourth_child = stat(file);

					return newNode;
				} else {
					cout << "Error: We have an invalid token provided - Expected then keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
					exit(1);
				}	
			} else {
				cout << "Error: We have an invalid token provided - Expected close bracket but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
				exit(1);
			}
		} else {
			cout << "Error: We have an invalid token provided - Expected open bracket but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		cout << "Error: We have an invalid token provided - Expected if keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1); 
	}
}

// Define our loop node
node* loop(ifstream& file) {
	if (tk.tkIdentifier == loopTk) {
		level++;
		node *newNode = getNode("<loop>");
		newNode->nToken = tk;
		tk = scanner(file, lineNum);

		if (tk.tkIdentifier == open_bracketTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);
			newNode->first_child = expr(file);
			newNode->second_child = RO(file);
			newNode->third_child = expr(file);

			if (tk.tkIdentifier == close_bracketTk) {
				newNode->nToken3 = tk;
				tk = scanner(file, lineNum);
				newNode->fourth_child = stat(file);

				return newNode;
			} else {
				cout << "Error: We have an invalid token provided - Expected close bracket but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
				exit(1);
			}
		} else {
			cout << "Error: We have an invalid token provided - Expected open bracket but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		cout << "Error: We have an invalid token provided - Expected loop keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Define assign node
node* assign(ifstream& file) {
	if(tk.tkIdentifier == assignTk) {
		level++;
		node *newNode = getNode("<assign>");
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		if (tk.tkIdentifier == idTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);
			if (tk.tkIdentifier == colon_equalsTk) {
				newNode->nToken3 = tk;
				tk = scanner(file, lineNum);
				newNode->first_child = expr(file);

				return newNode;
			} else {
				cout << "Error: We have an invalid token provided - Expected colon equals but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
				exit(1);
			}
		} else {
			cout << "Error: We have an invalid token provided - Expected identifier but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);	
		}
	} else {
		cout << "Error: We have an invalid token provided - Expected assign keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Define RO node
node* RO(ifstream& file) {
	level++;
	node *newNode = getNode("<RO>");

	if (tk.tkIdentifier == great_eqTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		return newNode;
	} else if (tk.tkIdentifier == less_eqTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		return newNode;
	} else if (tk.tkIdentifier == double_equalsTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		return newNode;
	} else if (tk.tkIdentifier == open_bracketTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		if (tk.tkIdentifier == double_equalsTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);
			if (tk.tkIdentifier == close_bracketTk) {
				newNode->nToken3 = tk;
				tk = scanner(file, lineNum);
				return newNode;
			} else {
				cout << "Error: We have an invalid operator, expected equals.\n";
				exit(1);
			}
		} else {
			cout << "Error: We have an invalid operator, expected equals.\n";
			exit(1); 
		}
	} else if (tk.tkIdentifier == modulusTk) {
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		return newNode;
	} else {
		cout << "Error: Invalid token has been provided.\n";
		exit(1);
	}
}

// Define label node
node* label(ifstream& file) {
	if (tk.tkIdentifier == voidTk) {
		level++;
		node *newNode = getNode("<label>");
		newNode->nToken = tk;
		tk = scanner(file, lineNum);

		if (tk.tkIdentifier == idTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected identifier but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		cout << "Error: We have an invalid token provided - Expected void token but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
}

// Define our goto_F node
node* goto_F(ifstream& file) {
	if (tk.tkIdentifier == procTk) {
		level++;
		node *newNode = getNode("<goto>");
		newNode->nToken = tk;
		tk = scanner(file, lineNum);
		if (tk.tkIdentifier == idTk) {
			newNode->nToken2 = tk;
			tk = scanner(file, lineNum);

			return newNode;
		} else {
			cout << "Error: We have an invalid token provided - Expected identifier but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
			exit(1);
		}
	} else {
		cout << "Error: We have an invalid token provided - Expected proc keyword but was provided " << token_names[tk.tkIdentifier] << " at line " << level << "\n";
		exit(1);
	}
} 

// Define our parser node
node* parser(ifstream& ifile){
	node* nd;
	while(ifile) {
		tk = scanner(ifile, lineNum);
		nd = program(ifile); 
	}

	return nd;
}