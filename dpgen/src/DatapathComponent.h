/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/17/2016
Assignment: 2
File: DatapathComponent.h
Description: Datapath Component Class for dpgen program
*/

#ifndef DATAPATHCOMPONENT_H
#define DATAPATHCOMPONENT_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>
#include<algorithm>
#include"DataType.h"

class DatapathComponent {
private:
	std::string name;
	std::vector<DataType*> _componentInputs;
	std::vector<DataType*> _componentOutputs;
	int dataWidth;
	double delay;
	
	///* Datapath Component inputs */
	

	///* Datapath Component outputs */
	//Wire outWire;
	//Output outWire;

	///* FOR INFORMATION ONLY
	//	std::string validSymbols[13] = { "=","+" ,"-", "*", ">", "<","==", "?", ":", ">>", "<<", "/", "%"};
	//*/
	///*
	//FUNCT___SYM___
	//REG		=
	//ADD		+
	//SUB		-
	//MUL		*
	//COMP	<
	//COMP	>
	//COMP	==
	//MUX2x1	? :
	//SHR		>>
	//SHL		<<
	//DIV		/
	//MOD		%
	//INC		+1
	//DEC		-1
	//*/
	//std::string component[12];

public:
	/*Constructors*/
	DatapathComponent();
	DatapathComponent(std::string n, std::vector<DataType*> _inputs, std::vector<DataType*> _outputs);
	/*Methods*/
	std::string getName();
	void setName(std::string n);
	std::vector<DataType*> getInputs();
	void setInputs(std::vector<DataType*> _inputs);
	std::vector<DataType*> getOutputs();
	void setOutputs(std::vector<DataType*> _outputs);
	int getDataWidth();
	void setDataWidth(int dW);
	int getDelay();
	void setDelay(int d);
	void addInput(DataType* newInput);
	void addOutput(DataType* newOutput);
	void checkIfSigned();
	void determineDataWidth();
	void assignDelay();

};

#endif //DATAPATHCOMPONENT_H
