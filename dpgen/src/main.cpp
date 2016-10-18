/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 9/29/2016
Assignment: 2
File: main.cpp
Description: Main function for dpgen program
*/

#include "Circuit.h"

int main(int argc, char* argv[])
{
	Circuit newCircuit;

	if (!newCircuit.readFile(argv[1])) {
		return 0;
	}

	newCircuit.writeToFile(argv[1]);

	return 0;
}