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
	string checkChar;
	bool foundDataType;
	const std::string validDataTypes[12] = { "Int1", "Int2", "Int8", "Int16", "Int32", "Int64",
									  "UInt1", "UInt2", "UInt8", "UInt16", "UInt32","UInt64" };
	int i = 0;
	int j = 0;

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
			//getline(inputFile, checkString);
			inputFile >> checkString;

			foundDataType = false;

			for (i = 0; i < 12; ++i) {
				//go through valid data types and see which one it is
				if (!checkString.compare(validDataTypes[i])) {
					foundDataType = true;
					break;
				}
			}

			if (foundDataType) {
				getline(inputFile, checkString);
				createNewInputVariable(checkString, i);
				//for (j = 0; j < checkString.size(); ++j) {
				//	if (checkString.at(j) != ' ' && checkString.at(j) != ',') {
				//		if (j != checkString.size() - 1) {
				//			if (checkString.at(j + 1) == ' ' || checkString.at(j + 1) == ',') {
				//				checkChar = checkString.at(j);
				//				//inputFile >> checkString;
				//				switch (i) {
				//				case 0: createNewInput(checkChar, 1, DATAWIDTH_1);
				//					break;
				//				case 1: createNewInput(checkChar, 1, DATAWIDTH_2);
				//					break;
				//				case 2: createNewInput(checkChar, 1, DATAWIDTH_8);
				//					break;
				//				case 3: createNewInput(checkChar, 1, DATAWIDTH_16);
				//					break;
				//				case 4: createNewInput(checkChar, 1, DATAWIDTH_32);
				//					break;
				//				case 5: createNewInput(checkChar, 1, DATAWIDTH_64);
				//					break;
				//				case 6: createNewInput(checkChar, 0, DATAWIDTH_1);
				//					break;
				//				case 7: createNewInput(checkChar, 0, DATAWIDTH_2);
				//					break;
				//				case 8: createNewInput(checkChar, 0, DATAWIDTH_8);
				//					break;
				//				case 9: createNewInput(checkChar, 0, DATAWIDTH_16);
				//					break;
				//				case 10: createNewInput(checkChar, 0, DATAWIDTH_32);
				//					break;
				//				case 11: createNewInput(checkChar, 0, DATAWIDTH_64);
				//					break;
				//				}
				//			}
				//		}
				//		else if (j == checkString.size() - 1 && checkString.at(j - 1) == ' ') {
				//			checkChar = checkString.at(j);
				//			//inputFile >> checkString;
				//			switch (i) {
				//			case 0: createNewInput(checkChar, 1, DATAWIDTH_1);
				//				break;
				//			case 1: createNewInput(checkChar, 1, DATAWIDTH_2);
				//				break;
				//			case 2: createNewInput(checkChar, 1, DATAWIDTH_8);
				//				break;
				//			case 3: createNewInput(checkChar, 1, DATAWIDTH_16);
				//				break;
				//			case 4: createNewInput(checkChar, 1, DATAWIDTH_32);
				//				break;
				//			case 5: createNewInput(checkChar, 1, DATAWIDTH_64);
				//				break;
				//			case 6: createNewInput(checkChar, 0, DATAWIDTH_1);
				//				break;
				//			case 7: createNewInput(checkChar, 0, DATAWIDTH_2);
				//				break;
				//			case 8: createNewInput(checkChar, 0, DATAWIDTH_8);
				//				break;
				//			case 9: createNewInput(checkChar, 0, DATAWIDTH_16);
				//				break;
				//			case 10: createNewInput(checkChar, 0, DATAWIDTH_32);
				//				break;
				//			case 11: createNewInput(checkChar, 0, DATAWIDTH_64);
				//				break;
				//			}
				//		}
				//	}
				//}
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
				if (!checkString.compare(validDataTypes[i])) {
					foundDataType = true;
					break;
				}
			}

			if (foundDataType) {
				getline(inputFile, checkString);

				for (j = 0; j < checkString.size(); j++) {
					if (checkString.at(j) != ' ' && checkString.at(j) != ',') {
						if (j != checkString.size() - 1) {
							if (checkString.at(j + 1) == ' ' || checkString.at(j + 1) == ',') {
								checkChar = checkString.at(j);
								switch (i) {
								case 0: createNewOutput(checkChar, 1, DATAWIDTH_1);
									break;
								case 1: createNewOutput(checkChar, 1, DATAWIDTH_2);
									break;
								case 2: createNewOutput(checkChar, 1, DATAWIDTH_8);
									break;
								case 3: createNewOutput(checkChar, 1, DATAWIDTH_16);
									break;
								case 4: createNewOutput(checkChar, 1, DATAWIDTH_32);
									break;
								case 5: createNewOutput(checkChar, 1, DATAWIDTH_64);
									break;
								case 6: createNewOutput(checkChar, 0, DATAWIDTH_1);
									break;
								case 7: createNewOutput(checkChar, 0, DATAWIDTH_2);
									break;
								case 8: createNewOutput(checkChar, 0, DATAWIDTH_8);
									break;
								case 9: createNewOutput(checkChar, 0, DATAWIDTH_16);
									break;
								case 10: createNewOutput(checkChar, 0, DATAWIDTH_32);
									break;
								case 11: createNewOutput(checkChar, 0, DATAWIDTH_64);
									break;
								}
							}
						}
						else if (j == checkString.size() - 1 && checkString.at(j - 1) == ' ') {
							checkChar = checkString.at(j);
							switch (i) {
							case 0: createNewOutput(checkChar, 1, DATAWIDTH_1);
								break;
							case 1: createNewOutput(checkChar, 1, DATAWIDTH_2);
								break;
							case 2: createNewOutput(checkChar, 1, DATAWIDTH_8);
								break;
							case 3: createNewOutput(checkChar, 1, DATAWIDTH_16);
								break;
							case 4: createNewOutput(checkChar, 1, DATAWIDTH_32);
								break;
							case 5: createNewOutput(checkChar, 1, DATAWIDTH_64);
								break;
							case 6: createNewOutput(checkChar, 0, DATAWIDTH_1);
								break;
							case 7: createNewOutput(checkChar, 0, DATAWIDTH_2);
								break;
							case 8: createNewOutput(checkChar, 0, DATAWIDTH_8);
								break;
							case 9: createNewOutput(checkChar, 0, DATAWIDTH_16);
								break;
							case 10: createNewOutput(checkChar, 0, DATAWIDTH_32);
								break;
							case 11: createNewOutput(checkChar, 0, DATAWIDTH_64);
								break;
							}
						}
					}
				}
			}
			else {
				cout << "Error: Invalid Data type: " << checkString << " Exiting Program." << endl;
			}
		}
		else if (!checkString.compare("wire")) {
			inputFile >> checkString;

			foundDataType = false;

			for (i = 0; i < 12; ++i) {
				//go through valid data types and see which one it is
				if (!checkString.compare(validDataTypes[i])) {
					foundDataType = true;
					break;
				}
			}

			if (foundDataType) {
				getline(inputFile, checkString);
				for (j = 0; j < checkString.size(); ++j) {
					if (checkString.at(j) != ' ' && checkString.at(j) != ',') {
						if (j != checkString.size() - 1) {
							if (checkString.at(j + 1) == ' ' || checkString.at(j + 1) == ',') {
								checkChar = checkString.at(j);
								switch (i) {
								case 0: createNewWire(checkChar, 1, DATAWIDTH_1);
									break;
								case 1: createNewWire(checkChar, 1, DATAWIDTH_2);
									break;
								case 2: createNewWire(checkChar, 1, DATAWIDTH_8);
									break;
								case 3: createNewWire(checkChar, 1, DATAWIDTH_16);
									break;
								case 4: createNewWire(checkChar, 1, DATAWIDTH_32);
									break;
								case 5: createNewWire(checkChar, 1, DATAWIDTH_64);
									break;
								case 6: createNewWire(checkChar, 0, DATAWIDTH_1);
									break;
								case 7: createNewWire(checkChar, 0, DATAWIDTH_2);
									break;
								case 8: createNewWire(checkChar, 0, DATAWIDTH_8);
									break;
								case 9: createNewWire(checkChar, 0, DATAWIDTH_16);
									break;
								case 10: createNewWire(checkChar, 0, DATAWIDTH_32);
									break;
								case 11: createNewWire(checkChar, 0, DATAWIDTH_64);
									break;
								}
							}
						}
						else if (j == checkString.size() - 1 && checkString.at(j - 1) == ' ') {
							checkChar = checkString.at(j);
							switch (i) {
							case 0: createNewWire(checkChar, 1, DATAWIDTH_1);
								break;
							case 1: createNewWire(checkChar, 1, DATAWIDTH_2);
								break;
							case 2: createNewWire(checkChar, 1, DATAWIDTH_8);
								break;
							case 3: createNewWire(checkChar, 1, DATAWIDTH_16);
								break;
							case 4: createNewWire(checkChar, 1, DATAWIDTH_32);
								break;
							case 5: createNewWire(checkChar, 1, DATAWIDTH_64);
								break;
							case 6: createNewWire(checkChar, 0, DATAWIDTH_1);
								break;
							case 7: createNewWire(checkChar, 0, DATAWIDTH_2);
								break;
							case 8: createNewWire(checkChar, 0, DATAWIDTH_8);
								break;
							case 9: createNewWire(checkChar, 0, DATAWIDTH_16);
								break;
							case 10: createNewWire(checkChar, 0, DATAWIDTH_32);
								break;
							case 11: createNewWire(checkChar, 0, DATAWIDTH_64);
								break;
							}
						}
					}
				}
			}
			else {
				cout << "Error: Invalid Data type: " << checkString << " Exiting Program." << endl;
			}
		}
		else {
			//TODO: write commands for if there is no first word
		}

	}
		
	inputFile.close();

}

void Circuit::writeToFile(char* fileName)
{
	int i = 0;

	cout << "Inputs" << endl;
	for (i = 0; i < _inputs.size(); ++i) {
		cout << _inputs.at(i).getName() << " " << _inputs.at(i).getDataWidth() << endl;
	}
	cout << "Outputs" << endl;
	for (i = 0; i < _outputs.size(); ++i) {
		cout << _outputs.at(i).getName() << " " << _outputs.at(i).getDataWidth() << endl;
	}
	cout << "Wires" << endl;
	for (i = 0; i < _wires.size(); ++i) {
		cout << _wires.at(i).getName() << " " << _wires.at(i).getDataWidth() << endl;
	}
	
}

void Circuit::determineCriticalPath()
{
}

void Circuit::createNewInputVariable(std::string checkString, int dataWidthIndex)
{
	string checkChar;
	int j = 0;

	for (j = 0; j < checkString.size(); ++j) {
		if (checkString.at(j) != ' ' && checkString.at(j) != ',') {
			if (j != checkString.size() - 1) {
				if (checkString.at(j + 1) == ' ' || checkString.at(j + 1) == ',') {
					checkChar = checkString.at(j);
					//inputFile >> checkString;
					switch (dataWidthIndex) {
					case 0: createNewInput(checkChar, 1, DATAWIDTH_1);
						break;
					case 1: createNewInput(checkChar, 1, DATAWIDTH_2);
						break;
					case 2: createNewInput(checkChar, 1, DATAWIDTH_8);
						break;
					case 3: createNewInput(checkChar, 1, DATAWIDTH_16);
						break;
					case 4: createNewInput(checkChar, 1, DATAWIDTH_32);
						break;
					case 5: createNewInput(checkChar, 1, DATAWIDTH_64);
						break;
					case 6: createNewInput(checkChar, 0, DATAWIDTH_1);
						break;
					case 7: createNewInput(checkChar, 0, DATAWIDTH_2);
						break;
					case 8: createNewInput(checkChar, 0, DATAWIDTH_8);
						break;
					case 9: createNewInput(checkChar, 0, DATAWIDTH_16);
						break;
					case 10: createNewInput(checkChar, 0, DATAWIDTH_32);
						break;
					case 11: createNewInput(checkChar, 0, DATAWIDTH_64);
						break;
					}
				}
			}
			else if (j == checkString.size() - 1 && checkString.at(j - 1) == ' ') {
				checkChar = checkString.at(j);
				//inputFile >> checkString;
				switch (dataWidthIndex) {
				case 0: createNewInput(checkChar, 1, DATAWIDTH_1);
					break;
				case 1: createNewInput(checkChar, 1, DATAWIDTH_2);
					break;
				case 2: createNewInput(checkChar, 1, DATAWIDTH_8);
					break;
				case 3: createNewInput(checkChar, 1, DATAWIDTH_16);
					break;
				case 4: createNewInput(checkChar, 1, DATAWIDTH_32);
					break;
				case 5: createNewInput(checkChar, 1, DATAWIDTH_64);
					break;
				case 6: createNewInput(checkChar, 0, DATAWIDTH_1);
					break;
				case 7: createNewInput(checkChar, 0, DATAWIDTH_2);
					break;
				case 8: createNewInput(checkChar, 0, DATAWIDTH_8);
					break;
				case 9: createNewInput(checkChar, 0, DATAWIDTH_16);
					break;
				case 10: createNewInput(checkChar, 0, DATAWIDTH_32);
					break;
				case 11: createNewInput(checkChar, 0, DATAWIDTH_64);
					break;
				}
			}
		}
	}
}

void Circuit::createNewOutputVariable(std::string checkString, int dataWidthIndex)
{
	string checkChar;
	int j = 0;
}

void Circuit::createNewWireVariable(std::string checkString, int dataWidthIndex)
{
	string checkChar;
	int j = 0;
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
