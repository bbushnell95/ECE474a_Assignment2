/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/3/2016
Assignment: 2
File: Circuit.cpp
Description: Circuit Class definitions for dpgen program
*/

#include "Circuit.h"
using namespace std;

Circuit::Circuit()
{
	outputCircuit = "";
	criticalPath = 0.0;
}


double Circuit::getCriticalPath()
{
	return criticalPath;
}

void Circuit::setCriticalPath(double cp)
{
	criticalPath = cp;
}

bool Circuit::readFile(char* fileName)
{
	ifstream inputFile;
	string checkString;

	inputFile.open(fileName);

	//checking if open
	if (!inputFile.is_open()) {
		cout << "Could not open " << fileName << endl;
		return false;	
	}

	//while there is something on the line
	while (!inputFile.fail()) {
		inputFile >> checkString;

		//TODO: do a case or if statement checking if the symbol matches up
	}

	inputFile.close();

}

void Circuit::writeToFile(char* fileName)
{
}

void Circuit::determineCriticalPath()
{
}
