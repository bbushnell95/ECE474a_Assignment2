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
	int componentOutputIndex = -1;
	int componentInputIndex = -1;
	int componentWireIndex = -1;

	inputFile.open(fileName);

	//checking if open
	if (!inputFile.is_open()) {
		// cout << "Could not open " << fileName << endl;
		return false;
	}

	//while there is something on the line
	while (!inputFile.eof()) {
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
			if (!checkVariable(checkString, &componentOutputIndex, &componentInputIndex, &componentWireIndex)) {
				cout << "Variable '" << checkString << "' not found, please correct Netlist Behavior File." << endl;
				return false;
			}
			else {
				getline(inputFile, checkString);
				if (componentOutputIndex != -1) {
					determineComponent(checkString, _outputs.at(componentOutputIndex));
				}
				else if (componentWireIndex != -1) {
					determineComponent(checkString, _wires.at(componentWireIndex));
				}
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

	}
	for (i = 0; i < _datapathComponents.size(); ++i) {
		_datapathComponents.at(i).determineDataWidth();
		_datapathComponents.at(i).assignDelay();
		_datapathComponents.at(i).checkIfSigned();
		//set going to for inputs
		for (j = 0; j < _datapathComponents.at(i).getInputs().size(); ++j) {
			_datapathComponents.at(i).getInputs().at(j).addToGoingTo(&_datapathComponents.at(i));
		}
		//sets coming from for outputs
		for (j = 0; j < _datapathComponents.at(i).getOutputs().size(); ++j) {
			_datapathComponents.at(i).getOutputs().at(j).addToComingFrom(&_datapathComponents.at(i));
		}
	}

	inputFile.close();
	return true;

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
	int k = 0;
	int naCount = 0;

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
	if (!outputFile.is_open()) {
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
	outputFile << "//Date Created: " << asctime(localtime(&timeNow));
	outputFile << "//Assignment: " << "2" << endl;
	outputFile << "//File: " << moduleName << ".v" << endl;
	outputFile << "//Description: A netlist behavior circuit implementation" << endl;
	outputFile << "//" << endl;
	outputFile << "//////////////////////////////////////////////////////////////////////////////////" << endl;
	outputFile << endl << endl;

	/* Start of Module. */
	outputFile << "module " << moduleName << "(clk, rst, ";
	for (i = 0; i < _inputs.size(); i++) {
		outputFile << _inputs.at(i).getName();
		outputFile << ", ";
	}
	for (i = 0; i < _outputs.size(); i++) {
		outputFile << _outputs.at(i).getName();
		if (i != _outputs.size() - 1) {
			outputFile << ", ";
		}
	}
	outputFile << ");" << endl;

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
		if (_outputs.at(i).getDataWidth() != DATAWIDTH_1) {
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
		if (_wires.at(i).getDataWidth() != DATAWIDTH_1) {
			outputFile << "[" << _wires.at(i).getDataWidth() - 1 << ":0] ";
		}
		outputFile << _wires.at(i).getName() << ";" << endl;
	}
	outputFile << endl;

	/* TODO: CHECK FOR NECESSARY N/A INPUTS TO DATAPATH
	COMPONENTS SUCH AS THE COMPARATOR. */
	/* Check for all N/A wires are necessary. */
	k = 0;
	for (i = 0; i < _datapathComponents.size(); i++) {
		if (!_datapathComponents.at(i).getName().compare("COMP_lt")) {
			outputFile << "\t" << "wire ";
			outputFile << "na" << k << " ";
			k++;
			outputFile << "na" << k << ";" << endl;
			k++;
		}
		else if (!_datapathComponents.at(i).getName().compare("SCOMP_lt")) {
			outputFile << "\t" << "wire ";
			outputFile << "na" << k << " ";
			k++;
			outputFile << "na" << k << ";" << endl;
			k++;
		}
		else if (!_datapathComponents.at(i).getName().compare("COMP_gt")) {
			outputFile << "\t" << "wire ";
			outputFile << "na" << k << " ";
			k++;
			outputFile << "na" << k << ";" << endl;
			k++;
		}
		else if (!_datapathComponents.at(i).getName().compare("SCOMP_gt")) {
			outputFile << "\t" << "wire ";
			outputFile << "na" << k << ", ";
			k++;
			outputFile << "na" << k << ";" << endl;
			k++;
		}
	}
	outputFile << endl;

	/* WRITE THE DATAPATH COMPONENTS. */
	k = 0;
	for (i = 0; i < _datapathComponents.size(); i++) {
		outputFile << "\t";
		/* Which module is it? */
		if ((!_datapathComponents.at(i).getName().compare("COMP_lt"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_lt"))
			|| (!_datapathComponents.at(i).getName().compare("COMP_gt"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_gt"))
			|| (!_datapathComponents.at(i).getName().compare("COMP_eq"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_eq"))) {
			outputFile << "SCOMP";
		}
		else {
			outputFile << _datapathComponents.at(i).getName();
		}

		/* What is the Datawidth? */
		outputFile << " #(";
		outputFile << _datapathComponents.at(i).getDataWidth();
		outputFile << ") ";

		/* Name the module. */
		if ((!_datapathComponents.at(i).getName().compare("COMP_lt"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_lt"))
			|| (!_datapathComponents.at(i).getName().compare("COMP_gt"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_gt"))
			|| (!_datapathComponents.at(i).getName().compare("COMP_eq"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_eq"))) {
			outputFile << "SCOMP";
		}
		else {
			outputFile << _datapathComponents.at(i).getName();
		}

		/* REG */
		outputFile << "_" << i << "(";
		if ((!_datapathComponents.at(i).getName().compare("REG"))
			|| (!_datapathComponents.at(i).getName().compare("SREG"))) {
			outputFile << _datapathComponents.at(i).getInputs().at(0).getName() << ", ";
			outputFile << "clk, rst, ";
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName();
		}
		/* ADD, SUB, MUL, DIV, MOD, SHL, SHR, INC, DEC */
		else if ((!_datapathComponents.at(i).getName().compare("ADD"))
			|| (!_datapathComponents.at(i).getName().compare("SADD"))
			|| (!_datapathComponents.at(i).getName().compare("SUB"))
			|| (!_datapathComponents.at(i).getName().compare("SSUB"))
			|| (!_datapathComponents.at(i).getName().compare("MUL"))
			|| (!_datapathComponents.at(i).getName().compare("SMUL"))
			|| (!_datapathComponents.at(i).getName().compare("DIV"))
			|| (!_datapathComponents.at(i).getName().compare("SDIV"))
			|| (!_datapathComponents.at(i).getName().compare("MOD"))
			|| (!_datapathComponents.at(i).getName().compare("SMOD"))
			|| (!_datapathComponents.at(i).getName().compare("SHR"))
			|| (!_datapathComponents.at(i).getName().compare("SSHR"))
			|| (!_datapathComponents.at(i).getName().compare("SHL"))
			|| (!_datapathComponents.at(i).getName().compare("SSHL"))
			|| (!_datapathComponents.at(i).getName().compare("INC"))
			|| (!_datapathComponents.at(i).getName().compare("SINC"))
			|| (!_datapathComponents.at(i).getName().compare("DEC"))
			|| (!_datapathComponents.at(i).getName().compare("SDEC"))) {
			for (j = 0; j < _datapathComponents.at(i).getInputs().size(); j++) {
				outputFile << _datapathComponents.at(i).getInputs().at(j).getName() << ", ";
			}
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName();
		}
		/* SHR, SHL */
		/* DON'T NEED. PLEASE LEAVE FOR NOW
		else if ((!_datapathComponents.at(i).getName().compare("SHL"))
			|| (!_datapathComponents.at(i).getName().compare("SSHL"))
			|| (!_datapathComponents.at(i).getName().compare("SHR"))
			|| (!_datapathComponents.at(i).getName().compare("SSHR"))) {
			// SHR (a, sh_amt, d);
			outputFile << _datapathComponents.at(i).getInputs().at()
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName();

		}
		*/
		/* MUL2x1 */
		else if ((!_datapathComponents.at(i).getName().compare("MUX2x1"))
			|| (!_datapathComponents.at(i).getName().compare("SMUX2x1"))) {
			// MUX2x1(a, b, sel, d);
			outputFile << _datapathComponents.at(i).getInputs().at(1).getName() << ", ";
			outputFile << _datapathComponents.at(i).getInputs().at(2).getName() << ", ";
			outputFile << _datapathComponents.at(i).getInputs().at(0).getName() << ", ";
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName();
		}
		/* INC, DEC */
		/* DON'T NEED. PLEASE LEAVE FOR NOW.
		else if ((!_datapathComponents.at(i).getName().compare("INC"))
			|| (!_datapathComponents.at(i).getName().compare("SINC"))
			|| (!_datapathComponents.at(i).getName().compare("DEC"))
			|| (!_datapathComponents.at(i).getName().compare("SDEC"))) {
			outputFile << _datapathComponents.at(i).getInputs().at(0).getName();
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName();
		}
		*/
		/* COMP_gt */
		else if ((!_datapathComponents.at(i).getName().compare("COMP_gt"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_gt"))) {
			for (j = 0; j < _datapathComponents.at(i).getInputs().size(); j++) {
				outputFile << _datapathComponents.at(i).getInputs().at(j).getName() << ", ";
			}
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName() << ", ";
			outputFile << "na" << k << ", ";
			k++;
			outputFile << "na" << k;
			k++;
		}
		/* COMP_lt */
		else if ((!_datapathComponents.at(i).getName().compare("COMP_lt"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_lt"))) {
			for (j = 0; j < _datapathComponents.at(i).getInputs().size(); j++) {
				outputFile << _datapathComponents.at(i).getInputs().at(j).getName() << ", ";
			}
			outputFile << "na" << k << ", ";
			k++;
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName() << ", ";
			outputFile << "na" << k;
			k++;
		}
		/* COMP_eq */
		else if ((!_datapathComponents.at(i).getName().compare("COMP_eq"))
			|| (!_datapathComponents.at(i).getName().compare("SCOMP_eq"))) {
			for (j = 0; j < _datapathComponents.at(i).getInputs().size(); j++) {
				outputFile << _datapathComponents.at(i).getInputs().at(j).getName() << ", ";
			}
			outputFile << "na" << k << ", ";
			k++;
			outputFile << "na" << k << ", ";
			k++;
			outputFile << _datapathComponents.at(i).getOutputs().at(0).getName();
		}
		outputFile << ");" << endl;
	}

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

bool Circuit::checkVariable(std::string checkName, int* outputIndex, int* inputIndex, int* wireIndex)
{
	bool variableFound = false;
	int i = 0;

	/*check if in inputs*/
	for (i = 0; i < _inputs.size(); ++i) {
		if (!_inputs.at(i).getName().compare(checkName)) {
			variableFound = true;
			*inputIndex = i;
			break;
		}
	}

	/*check if in wires*/
	for (i = 0; i < _wires.size(); ++i) {
		if (!_wires.at(i).getName().compare(checkName)) {
			variableFound = true;
			*wireIndex = i;
			break;
		}
	}

	/*check if in outputs*/
	for (i = 0; i < _outputs.size(); ++i) {
		if (!_outputs.at(i).getName().compare(checkName)) {
			variableFound = true;
			*outputIndex = i;
			break;
		}
	}
	return variableFound;
}
bool Circuit::determineComponent(std::string line, DataType output)
{
	int i = 0;
	int equalCount = 0;
	int inputIndex = -1;
	int wireIndex = -1;
	int outputIndex = -1;
	bool result = true;
	std::string checkString = ""; 
	std::string componentType = "";
	std::string tempVariableName = "";
	std::vector<DataType> componentInputs;
	std::vector<DataType> componentOutputs;
	std::istringstream iss(line);

	//line += '\n';
	componentOutputs.push_back(output);

	while (!iss.eof()) {
		iss >> checkString;

		if (!checkString.compare("=")) {
			++equalCount;
		}
		else {
			if (!checkValidSymbol(checkString, &componentType)) {
				if (checkVariable(checkString, &outputIndex, &inputIndex, &wireIndex)) {
					if (inputIndex != -1) {
						componentInputs.push_back(_inputs.at(inputIndex));

					}
					else if (wireIndex != -1) {
						componentInputs.push_back(_wires.at(wireIndex));
					}
				}
				else {
					cout << checkString << " is not a valid variable or symbol" << endl;
					result = false;
				}
			}

		}
	}
	if (result) {
		if (componentInputs.size() == 1) {
			createNewDatapathComponent("REG", componentInputs, componentOutputs);
		}
		else {
			createNewDatapathComponent(componentType, componentInputs, componentOutputs);
		}
	}
	return result;

}

void Circuit::createNewDatapathComponent(std::string name, std::vector<DataType> _inputs, std::vector<DataType> _outputs) 
{
	DatapathComponent* newComponent = new DatapathComponent(name, _inputs, _outputs);

	_datapathComponents.push_back(*newComponent);

}


bool Circuit::checkValidSymbol(std::string checkSymbol, std::string* dPType) 
{
	const std::string validSymbols[13] = { "=","+" ,"-", "*", ">", "<","==", "?", ":", ">>", "<<", "/", "%" };
	int i = 0;
	bool foundValidSymbol = false;

	for (i = 0; i < 13; i++) {
		if (!checkSymbol.compare(validSymbols[i])) {
			foundValidSymbol = true;
			break;
		}
	}

	if (!foundValidSymbol) {
		return false;
	}

	switch (i) {
	case 0:
		// Do nothing.
		break;
	case 1: *dPType = "ADD";
		break;
	case 2: *dPType = "SUB";
		break;
	case 3: *dPType = "MUL";
		break;
	case 4: *dPType = "COMP_gt";
		break;
	case 5: *dPType = "COMP_lt";
		break;
	case 6: *dPType = "COMP_eq";
		break;
	case 7: *dPType = "MUX2x1";
		break;
	case 8: *dPType = "MUX2x1";
		break;
	case 9: *dPType = "SHR";
		break;
	case 10: *dPType = "SHL";
		break;
	case 11: *dPType = "DIV";
		break;
	case 12: *dPType = "MOD";
		break;
	}

	return true;
}

