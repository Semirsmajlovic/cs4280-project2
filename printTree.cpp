// Define our includes
#include <iostream>
#include "printTree.h"

// Define our variable
static int level = 0;

// List of token names.
string token_name[] = {
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

// Prints the tree in preorder
void printTree(node *pTree) {
        if (pTree != NULL) {
                token tk = pTree->nToken;
                for (int i = 0 ; i < pTree->level ; i++) { 
                        cout << "  ";
                }
                cout << pTree->name << "\t";

                if (tk.tkName != "") {
                        cout << "| Our Token ID: " << token_name[tk.tkIdentifier] << ", Current Instance: " << tk.tkName << ", Defined at Line: " << tk.lineNum << " |\n"; 
                        tk = pTree->nToken2;
                        if (token_name[tk.tkIdentifier] != "End of File") {
                                for (int i = 0 ; i < level ; i++) {
                                        cout << "  ";
                                }			
                                cout << "\t\t| Our Token ID: " << token_name[tk.tkIdentifier] << ", Current Instance: " << tk.tkName << ", Defined at Line: " << tk.lineNum << " |\n";
                                tk = pTree->nToken3; 
                                if (token_name[tk.tkIdentifier] != "End of File") {
                                        for (int i = 0 ; i < level ; i++) {
                                                cout << "  ";
                                        }
                                        cout << "\t\t| Our Token ID: " << token_name[tk.tkIdentifier] << ", Current Instance: " << tk.tkName << ", Defined at Line: " << tk.lineNum << " |\n";
                                        tk = pTree->nToken4;
                                        if (token_name[tk.tkIdentifier] != "End of File") {
                                                for (int i = 0 ; i < level ; i++) { 
                                                        cout << "  ";
                                                }
                                                cout << "\t\t| Our Token ID: " << token_name[tk.tkIdentifier] << ", Current Instance: " << tk.tkName << ", Defined at Line: " << tk.lineNum << " |\n";
                                                tk = pTree->nToken5;
                                                if (token_name[tk.tkIdentifier] != "End of File") {
                                                        for (int i = 0 ; i < level ; i++) {
                                                                cout << "  ";
                                                        }
                                                        cout << "\t\t| Our Token ID: " << token_name[tk.tkIdentifier] << ", Current Instance: " << tk.tkName << ", Defined at Line: " << tk.lineNum << " |\n";
                                                }
                                        }
                                }		
                        }
                }
                cout << "\n";
                
                // Process our children
                printTree(pTree->first_child);
                printTree(pTree->second_child);
                printTree(pTree->third_child);
                printTree(pTree->fourth_child);
        }
}
