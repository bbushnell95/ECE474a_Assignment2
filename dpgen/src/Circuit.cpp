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
	bool foundSymbol;
	const std::string validDataTypes[12] = { "Int1", "Int2", "Int8", "Int16", "Int32", "Int64",
									  "UInt1", "UInt2", "UInt8", "UInt16", "UInt32","UInt64" };
	const std::string validSymbols[13] = { "=","+" ,"-", "*", ">", "<","==", "?", ":", ">>", "<<", "/", "%"};
	int i = 0;
	int j = 0;

	inputFile.open(fileName);

	//checking if open
	if (!inputFile.is_open()) {
		// cout << "Could not open " << fileName << endl;
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
				createNewOutputVariable(checkString, i);
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
				createNewWireVariable(checkString, i);
			}
			else {
				cout << "Error: Invalid Data type: " << checkString << " Exiting Program." << endl;
			}
		}
		else {
			//TODO: write commands for if there is no first word
			
			// TODO: CHECK FOR VALID OUTPUT/WIRE FIRST

			// TODO: READ IN REST OF LINE AND PARSE

			// TODO: SEE WHAT TYPE OF DATAPATH COMPONENT IS PRESENT.

			/*
			inputFile >> checkString;
			foundSymbol = false;
			for (i = 0; i < 12; ++i) {
				//go through valid data types and see which one it is
				if (!checkString.compare(validSymbols[i])) {
					foundSymbol = true;
					break;
				}
			}
			if (foundDataType) {
				// TODO: HANDLE IF/ELSE TO MUX/REG/OTHERS IN HERE.
				getline(inputFile, checkString);
				createNewInputVariable(checkString, i);
			}
			else {
				cout << "Error: Invalid Datapath Component: " << checkString << " Exiting Program." << endl;
			}
			*/

		}

	}
		
	inputFile.close();

}

bool Circuit::writeToFile(char* fileName)
{
	/* Set up variables. */
	ofstream outputFile;
	time_t timeNow = time(0);
	string tempFileName = "";
	string moduleName = "";
	int i = 0;
	int j = 0;

	/* Staging file name. */
	tempFileName = fileName;
	for (i = tempFileName.size() - 1; i > 0; i--) {
		if (tempFileName.at(i) == '\\') {
			break;
		}
	}
	for (i = i + 1; i < tempFileName.size() - 1; i++) {
		if (tempFileName.at(i) == '.') {
			break;
		}
		moduleName += tempFileName.at(i);
	}

	/* Open the output file. */
	outputFile.open(fileName);
	if ( !outputFile.is_open() ) {
		return false;
	}

	/* Check for empty netlist behavior files. */
	if (_inputs.empty()) {
		outputFile.close();
		return false;
	}
	if (_outputs.empty()) {
		outputFile.close();
		return false;
	}
	/* Note: There can be no wires if there is 
	a netlist behavior file containing no
	inter-connected datapath components. */
	
	/* Print Setup. */
	outputFile << "`timescale 1ns / 1ps" << endl;
	outputFile << "//////////////////////////////////////////////////////////////////////////////////" << endl;
	outputFile << "//" << endl;
	outputFile << "//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)" << endl;
	outputFile << "//Date Created: " << asctime(localtime(&timeNow)) << endl;;
	outputFile << endl;
	outputFile << "//Assignment: " << "2" << endl;
	outputFile << "//File: " << moduleName << ".v" << endl;
	outputFile << "//Description: Netlist Behavior circuit implementation for "<< fileName << endl;
	outputFile << "//" << endl;
	outputFile << "//////////////////////////////////////////////////////////////////////////////////" << endl;
	outputFile << endl << endl;

	/* Start of Module. */
	outputFile << "module " << moduleName << "(Clk, Rst, ";
	for (i = 0; i < _inputs.size(); i++) {
		outputFile << _inputs.at(i).getName();
		if (i != _inputs.size() - 1) {
			outputFile << ", ";
		}
	}
	outputFile << ");" << endl;

	/* TODO: CHECK FOR NECESSARY CLK, RST. */
	/* TODO: CHECK FOR NECESSARY N/A INPUTS TO DATAPATH
			 COMPONENTS SUCH AS THE COMPARATOR. */
	
	/* Print Inputs. */
	// cout << "Inputs" << endl;
	for (i = 0; i < _inputs.size(); i++) {
		// cout << _inputs.at(i).getName() << " " << _inputs.at(i).getDataWidth() << endl;
		outputFile << "\t" << "input ";
		if (_inputs.at(i).getDataWidth() != DATAWIDTH_1) {
			outputFile << "[" << _inputs.at(i).getDataWidth() - 1 << ":0] ";
		}
		outputFile << _inputs.at(i).getName() << ";" << endl;
	}
	outputFile << endl;

	/* Print Outputs. */
	// cout << "Outputs" << endl;
	for (i = 0; i < _outputs.size(); i++) {
		// cout << _outputs.at(i).getName() << " " << _outputs.at(i).getDataWidth() << endl;
		outputFile << "\t" << "output ";
		if ( _outputs.at(i).getDataWidth() != DATAWIDTH_1 ) {
			outputFile << "[" << _outputs.at(i).getDataWidth() - 1 << ":0] ";
		}
		outputFile << _outputs.at(i).getName() << ";" << endl;
	}
	outputFile << endl;

	/* Print Wires. */
	// cout << "Wires" << endl;
	for (i = 0; i < _wires.size(); i++) {
		// cout << _wires.at(i).getName() << " " << _wires.at(i).getDataWidth() << endl;
		outputFile << "\t" << "wire ";
		if ( _wires.at(i).getDataWidth() != DATAWIDTH_1 ) {
			outputFile << "[" << _wires.at(i).getDataWidth() - 1 << ":0] ";
		}
		outputFile << _wires.at(i).getName() << ";" << endl;
	}
	outputFile << endl;

	/* TODO: WRITE THE DATAPATH COMPONENTS. */

	/* End Module. */
	outputFile << endl << "endmodule" << endl;
	
	/* Close the output file. */
	outputFile.close();
	
	return true;

}

void Circuit::determineCriticalPath()
{

}

void Circuit::createNewInputVariable(std::string checkString, int dataWidthIndex)
{
	string checkChar = "";
	string variableName = "";
	int j = 0;

	checkString += '\n';

	for (j = 0; j < checkString.size()-1; ++j) {
		if (checkString.at(j) != ' ' && checkString.at(j) != ',') {
			if (j != checkString.size() - 2) {
				if ((checkString.at(j + 1) == ' ' || checkString.at(j + 1) == ',') && !variableName.compare("")) {
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
				else {
					if (checkString.at(j + 1) == ',' || checkString.at(j + 1) == '\n') {
						switch (dataWidthIndex) {
						case 0: createNewInput(variableName, 1, DATAWIDTH_1);
							break;
						case 1: createNewInput(variableName, 1, DATAWIDTH_2);
							break;
						case 2: createNewInput(variableName, 1, DATAWIDTH_8);
							break;
						case 3: createNewInput(variableName, 1, DATAWIDTH_16);
							break;
						case 4: createNewInput(variableName, 1, DATAWIDTH_32);
							break;
						case 5: createNewInput(variableName, 1, DATAWIDTH_64);
							break;
						case 6: createNewInput(variableName, 0, DATAWIDTH_1);
							break;
						case 7: createNewInput(variableName, 0, DATAWIDTH_2);
							break;
						case 8: createNewInput(variableName, 0, DATAWIDTH_8);
							break;
						case 9: createNewInput(variableName, 0, DATAWIDTH_16);
							break;
						case 10: createNewInput(variableName, 0, DATAWIDTH_32);
							break;
						case 11: createNewInput(variableName, 0, DATAWIDTH_64);
							break;
						}
						variableName = "";
					}
					else {
						variableName += checkString.at(j);
					}
				}
			}
			else if (j == checkString.size() - 2 && checkString.at(j - 1) == ' ' && checkString.at(j) != '\n') {
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
			else {
				if (variableName.compare("")) {
					variableName += checkString.at(j);
					switch (dataWidthIndex) {
					case 0: createNewInput(variableName, 1, DATAWIDTH_1);
						break;
					case 1: createNewInput(variableName, 1, DATAWIDTH_2);
						break;
					case 2: createNewInput(variableName, 1, DATAWIDTH_8);
						break;
					case 3: createNewInput(variableName, 1, DATAWIDTH_16);
						break;
					case 4: createNewInput(variableName, 1, DATAWIDTH_32);
						break;
					case 5: createNewInput(variableName, 1, DATAWIDTH_64);
						break;
					case 6: createNewInput(variableName, 0, DATAWIDTH_1);
						break;
					case 7: createNewInput(variableName, 0, DATAWIDTH_2);
						break;
					case 8: createNewInput(variableName, 0, DATAWIDTH_8);
						break;
					case 9: createNewInput(variableName, 0, DATAWIDTH_16);
						break;
					case 10: createNewInput(variableName, 0, DATAWIDTH_32);
						break;
					case 11: createNewInput(variableName, 0, DATAWIDTH_64);
						break;
					}
					variableName = "";
				}
			}
		}
	}
}

void Circuit::createNewOutputVariable(std::string checkString, int dataWidthIndex)
{
	string checkChar = "";
	string variableName = "";
	int j = 0;

	checkString += '\n';
	for (j = 0; j < checkString.size()-1; j++) {
		if (checkString.at(j) != ' ' && checkString.at(j) != ',') {
			if (j != checkString.size() - 2) {
				if ((checkString.at(j + 1) == ' ' || checkString.at(j + 1) == ',') && !variableName.compare("")) {
					checkChar = checkString.at(j);
					switch (dataWidthIndex) {
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
				else {
					if (checkString.at(j + 1) == ',' || checkString.at(j + 1) == '\n') {
						variableName += checkString.at(j);
						switch (dataWidthIndex) {
						case 0: createNewOutput(variableName, 1, DATAWIDTH_1);
							break;
						case 1: createNewOutput(variableName, 1, DATAWIDTH_2);
							break;
						case 2: createNewOutput(variableName, 1, DATAWIDTH_8);
							break;
						case 3: createNewOutput(variableName, 1, DATAWIDTH_16);
							break;
						case 4: createNewOutput(variableName, 1, DATAWIDTH_32);
							break;
						case 5: createNewOutput(variableName, 1, DATAWIDTH_64);
							break;
						case 6: createNewOutput(variableName, 0, DATAWIDTH_1);
							break;
						case 7: createNewOutput(variableName, 0, DATAWIDTH_2);
							break;
						case 8: createNewOutput(variableName, 0, DATAWIDTH_8);
							break;
						case 9: createNewOutput(variableName, 0, DATAWIDTH_16);
							break;
						case 10: createNewOutput(variableName, 0, DATAWIDTH_32);
							break;
						case 11: createNewOutput(variableName, 0, DATAWIDTH_64);
							break;
						}
						variableName = "";
					}
					else {
						variableName += checkString.at(j);
					}
				}
			}
			else if (j == checkString.size() - 2 && checkString.at(j - 1) == ' ' && checkString.at(j) != '\n') {
				checkChar = checkString.at(j);
				switch (dataWidthIndex) {
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
			else {
				if (variableName.compare("")) {
					variableName += checkString.at(j);
					switch (dataWidthIndex) {
					case 0: createNewOutput(variableName, 1, DATAWIDTH_1);
						break;
					case 1: createNewOutput(variableName, 1, DATAWIDTH_2);
						break;
					case 2: createNewOutput(variableName, 1, DATAWIDTH_8);
						break;
					case 3: createNewOutput(variableName, 1, DATAWIDTH_16);
						break;
					case 4: createNewOutput(variableName, 1, DATAWIDTH_32);
						break;
					case 5: createNewOutput(variableName, 1, DATAWIDTH_64);
						break;
					case 6: createNewOutput(variableName, 0, DATAWIDTH_1);
						break;
					case 7: createNewOutput(variableName, 0, DATAWIDTH_2);
						break;
					case 8: createNewOutput(variableName, 0, DATAWIDTH_8);
						break;
					case 9: createNewOutput(variableName, 0, DATAWIDTH_16);
						break;
					case 10: createNewOutput(variableName, 0, DATAWIDTH_32);
						break;
					case 11: createNewOutput(variableName, 0, DATAWIDTH_64);
						break;
					}
					variableName = "";
				}
			}
		}
	}
}

void Circuit::createNewWireVariable(std::string checkString, int dataWidthIndex)
{
	string checkChar = "";
	string variableName = "";
	int j = 0;

	checkString += '\n';

	for (j = 0; j < checkString.size()-1; ++j) {
		if (checkString.at(j) != ' ' && checkString.at(j) != ',') {
			if (j != checkString.size() - 2) {
				if ((checkString.at(j + 1) == ' ' || checkString.at(j + 1) == ',') && !variableName.compare("")) {
					checkChar = checkString.at(j);
					switch (dataWidthIndex) {
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
				else {
					if (checkString.at(j + 1) == ',' || checkString.at(j + 1) == '\n') {
						variableName += checkString.at(j);
						switch (dataWidthIndex) {
						case 0: createNewWire(variableName, 1, DATAWIDTH_1);
							break;
						case 1: createNewWire(variableName, 1, DATAWIDTH_2);
							break;
						case 2: createNewWire(variableName, 1, DATAWIDTH_8);
							break;
						case 3: createNewWire(variableName, 1, DATAWIDTH_16);
							break;
						case 4: createNewWire(variableName, 1, DATAWIDTH_32);
							break;
						case 5: createNewWire(variableName, 1, DATAWIDTH_64);
							break;
						case 6: createNewWire(variableName, 0, DATAWIDTH_1);
							break;
						case 7: createNewWire(variableName, 0, DATAWIDTH_2);
							break;
						case 8: createNewWire(variableName, 0, DATAWIDTH_8);
							break;
						case 9: createNewWire(variableName, 0, DATAWIDTH_16);
							break;
						case 10: createNewWire(variableName, 0, DATAWIDTH_32);
							break;
						case 11: createNewWire(variableName, 0, DATAWIDTH_64);
							break;
						}
						variableName = "";
					}
					else {
						variableName += checkString.at(j);
					}
				}
			}
			else if (j == checkString.size() - 2 && checkString.at(j - 1) == ' ' && checkString.at(j) != '\n') {
				checkChar = checkString.at(j);
				switch (dataWidthIndex) {
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
			else {
				if (variableName.compare("")) {
					variableName += checkString.at(j);
					switch (dataWidthIndex) {
					case 0: createNewWire(variableName, 1, DATAWIDTH_1);
						break;
					case 1: createNewWire(variableName, 1, DATAWIDTH_2);
						break;
					case 2: createNewWire(variableName, 1, DATAWIDTH_8);
						break;
					case 3: createNewWire(variableName, 1, DATAWIDTH_16);
						break;
					case 4: createNewWire(variableName, 1, DATAWIDTH_32);
						break;
					case 5: createNewWire(variableName, 1, DATAWIDTH_64);
						break;
					case 6: createNewWire(variableName, 0, DATAWIDTH_1);
						break;
					case 7: createNewWire(variableName, 0, DATAWIDTH_2);
						break;
					case 8: createNewWire(variableName, 0, DATAWIDTH_8);
						break;
					case 9: createNewWire(variableName, 0, DATAWIDTH_16);
						break;
					case 10: createNewWire(variableName, 0, DATAWIDTH_32);
						break;
					case 11: createNewWire(variableName, 0, DATAWIDTH_64);
						break;
					}
					variableName = "";
				}
			}
			
		}
	}
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

//void Circuit::createNewDatapathComponent(std::string name, etc.)