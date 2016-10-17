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
	bool foundDataType;
	const std::string validDataTypes[12] = { "Int1", "Int2", "Int8", "Int16", "Int32", "Int64",
									  "UInt1", "UInt2", "UInt8", "UInt16", "UInt32","UInt64" };
	int i = 0;

	inputFile.open(fileName);

	//checking if open
	if (!inputFile.is_open()) {
		cout << "Could not open " << fileName << endl;
		return false;	
	}

	//while there is something on the line
	while (!inputFile.fail()) {
		inputFile >> checkString;

		//first check if input or output or wire
		if (checkString.compare("input") == 0) {
			inputFile >> checkString;

			foundDataType = false;

			for (i = 0; i < 12; ++i) {
				//go through valid data types and see which one it is
				if (checkString.compare(validDataTypes[i])) {
					foundDataType = true;
					break;
				}
			}

			if (foundDataType) {
				switch (i) {
					//TODO: Write conditions for each case of i (0 - 5, signed integer, 6-11 unsigned int)
					case 0: break;
					case 1: break;
					case 2: break;
					case 3: break;
					case 4: break;
					case 5: break;
					case 6: break;
					case 7: break;
					case 8: break;
					case 9: break;
					case 10: break;
					case 11: break;
				}
			}
			else {
				cout << "Error: Invalid Data type: " << checkString << " Exiting Program." << endl;
			}
		}
		else if (checkString.compare("output") == 0) {
			//TODO: write commands for if first word is 'output'
		}
		else if (checkString.compare("wire")) {
			//TODO: write commands for if first word is 'wire'
		}
		else {
			//TODO: write commands for if there is no first word
		}

	}
		
	inputFile.close();

}

void Circuit::writeToFile(char* fileName)
{
}

void Circuit::determineCriticalPath()
{
}
