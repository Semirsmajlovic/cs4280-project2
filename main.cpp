// Introduce our includes.
#include <iostream>
#include <fstream>
#include "parser.h"
#include "printTree.h"

// Define our namespace.
using namespace std;

// Define our main function w/ parameters.
int main(int argc, char *argv[]) {
	
	// Define our variables
	string file_name;
	ifstream ifile;
	
	// If we have one argument, proceed with execution.
	if (argc == 1) {
		try {
			// Variables inside try/catch
			string user_input;
			ofstream temporary_file;

			// Handle temporary file.
			file_name = "temp.sp2022";
			temporary_file.open(file_name.c_str());

			// Define our while loop.
			while(getline(cin, user_input)) {
				temporary_file << user_input << "\n";
			}
			temporary_file.close();

		} catch(const ifstream::failure& e) {
			cout << "Error: The file could not be found.\n";
			return 1;
		}

	// Do we have two arguments?
	} else if(argc == 2) {
		file_name = argv[1];
		file_name.append(".sp2022");

	// Do we have more than two arguments?
	} else if(argc > 2) {
		cout << "Error: Please provide less than two arguments.\n";
		return 1;
	}
	
	// Open our file and call the test scanner.
	ifile.open(file_name.c_str());
	
	// Begin process of building tree.
	node *parse_tree = parser(ifile);

	// Print tree
	printTree(parse_tree);

	// Close input file
	cout << "\nThe file is now terminating...\n";
	ifile.close();
		
	return 0;
}
