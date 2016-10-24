/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 9/29/2016
Assignment: 2
File: main.cpp
Description: Main function for dpgen program
*/

#include <stdlib.h>
#include "Circuit.h"

using namespace std;

/* Command-line Argument as follows: 
dpgen netlistFile verilogFile
*/
int main(int argc, char *argv[])
{
	Circuit newCircuit;

	/* Check for the correct number of arguments */
	/*if (argc != 3) {
		cout << endl;
		cout << "Usage: " << argv[0] << "netlistFile outputFile";
		cout << endl << endl;
		return EXIT_FAILURE;
	}*/


	/* Read in the netlist file */
	if (!newCircuit.readFile(argv[1])) {
		cout << endl;
		cout << "Could not read from the input file " << argv[1] << ".";
		cout << endl << endl;
		return EXIT_FAILURE;
	}

	/* Write to the verilog file */
	if (!newCircuit.writeToFile(argv[2])) {
		cout << endl;
		cout << "Could not write to output file " << argv[2] << ".";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}