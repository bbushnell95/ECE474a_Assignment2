/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/3/2016
Assignment: 2
File: Circuit.h
Description: Circuit Class for dpgen program
*/

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <ctime>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cstring>
#include<algorithm>

#include "DatapathComponent.h"
#include "DataType.h"
#include "Input.h"
#include "Output.h"
#include "Wire.h"
#include "Register.h"


#define DATAWIDTH_1 1
#define DATAWIDTH_2 2
#define DATAWIDTH_8 8 
#define DATAWIDTH_16 16 
#define DATAWIDTH_32 32
#define DATAWIDTH_64 64


class Circuit {

private:
	std::string outputCircuit;
	std::vector<Input*> _inputs;
	std::vector<Output*> _outputs;
	std::vector<Wire*> _wires;
	std::vector<Register*> _registers;
	std::vector<DatapathComponent> _datapathComponents;
	double criticalPath;

public:
	/*Constructors*/
	Circuit();

	/*Getters and Setters*/
	double getCriticalPath();
	void setCriticalPath(double cp);

	/*Methods*/
	bool readFile(char* fileName);
	bool writeToFile(char* fileName);
	void determineCriticalPath();
	void visitComponent(DatapathComponent * compoenent, double currTime, double* cP);
	void createNewInputVariable(std::string checkString, int dataWidthIndex);
	void createNewOutputVariable(std::string checkString, int dataWidthIndex);
	void createNewWireVariable(std::string checkString, int dataWidthIndex);
	// void createNewRegisterVariable(std::string checkString, int dataWidthIndex);
	void createNewInput(std::string name, bool sign, int dataWidth);
	void createNewOutput(std::string name, bool sign, int dataWidth);
	void createNewWire(std::string name, bool sign, int dataWidth);
	// void createNewRegister(std::string name, bool sign, int dataWidth);
	bool checkVariable(std::string checkName, int* outputIndex, int* inputIndex, int* wireIndex);
	bool determineComponent(std::string line, DataType* output);
	void createNewDatapathComponent(std::string name, std::vector<DataType*> _Cinputs, std::vector<DataType*> _Coutputs);
	bool checkValidSymbol(std::string checkSymbol, std::string* dPType);
	bool writeInputsToFile(std::ofstream *outputFile, int i, int j);
	bool checkIfComment(std::string checkString);

};

#endif // CIRCUIT_H