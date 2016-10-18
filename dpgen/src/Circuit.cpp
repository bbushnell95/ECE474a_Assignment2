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
				inputFile >> checkString;
				switch (i) {		
					case 0: createNewInput(checkString, 1, DATAWIDTH_1);
					case 1: createNewInput(checkString, 1, DATAWIDTH_2);
					case 2: createNewInput(checkString, 1, DATAWIDTH_8);
					case 3: createNewInput(checkString, 1, DATAWIDTH_16);
					case 4: createNewInput(checkString, 1, DATAWIDTH_32);
					case 5: createNewInput(checkString, 1, DATAWIDTH_64);
					case 6: createNewInput(checkString, 0, DATAWIDTH_1);
					case 7: createNewInput(checkString, 0, DATAWIDTH_2);
					case 8: createNewInput(checkString, 0, DATAWIDTH_8);
					case 9: createNewInput(checkString, 0, DATAWIDTH_16);
					case 10: createNewInput(checkString, 0, DATAWIDTH_32);
					case 11: createNewInput(checkString, 0, DATAWIDTH_64);
				}
			}
			else {
				cout << "Error: Invalid Data type: " << checkString << " Exiting Program." << endl;
			}
		}
		else if (checkString.compare("output") == 0) {
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
				inputFile >> checkString;
				switch (i) {
					case 0: createNewOutput(checkString, 1, DATAWIDTH_1);
					case 1: createNewOutput(checkString, 1, DATAWIDTH_2);
					case 2: createNewOutput(checkString, 1, DATAWIDTH_8);
					case 3: createNewOutput(checkString, 1, DATAWIDTH_16);
					case 4: createNewOutput(checkString, 1, DATAWIDTH_32);
					case 5: createNewOutput(checkString, 1, DATAWIDTH_64);
					case 6: createNewOutput(checkString, 0, DATAWIDTH_1);
					case 7: createNewOutput(checkString, 0, DATAWIDTH_2);
					case 8: createNewOutput(checkString, 0, DATAWIDTH_8);
					case 9: createNewOutput(checkString, 0, DATAWIDTH_16);
					case 10: createNewOutput(checkString, 0, DATAWIDTH_32);
					case 11: createNewOutput(checkString, 0, DATAWIDTH_64);
				}
			}
			else {
				cout << "Error: Invalid Data type: " << checkString << " Exiting Program." << endl;
			}
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

void Circuit::createNewInput(std::string name, bool sign, int dataWidth)
{
	Input* newInput = new Input(name, sign, dataWidth);

	_inputs.push_back(*newInput);
}

void Circuit::createNewOutput(std::string name, bool sign, int dataWidth)
{
	Output* newOutput = new Output(name, sign, dataWidth);

	_outputs.push_back(*newOutput);
}

void Circuit::createNewWire(std::string name, bool sign, int dataWidth)
{
	Wire* newWire = new Wire(name, sign, dataWidth);

	_wires.push_back(*newWire);
}
