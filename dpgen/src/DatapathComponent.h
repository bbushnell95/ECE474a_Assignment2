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

#include "Input.h"
#include "Output.h"
#include "Wire.h"

class DatapathComponent {
private:
	std::string name;

	/* Datapath Component inputs */
	std::vector<Wire> inWire;
	std::vector<Input> inInput;

	/* Datapath Component outputs */
	Wire outWire;
	Output outWire;

	/* FOR INFORMATION ONLY
		std::string validSymbols[13] = { "=","+" ,"-", "*", ">", "<","==", "?", ":", ">>", "<<", "/", "%"};
	*/
	/*
	FUNCT___SYM___
	REG		=
	ADD		+
	SUB		-
	MUL		*
	COMP	<
	COMP	>
	COMP	==
	MUX2x1	? :
	SHR		>>
	SHL		<<
	DIV		/
	MOD		%
	INC		+1
	DEC		-1
	*/
	std::string component[12];

public:
	/*Constructors*/
	DatapathComponent();

	/*Methods*/
	
};

#endif
