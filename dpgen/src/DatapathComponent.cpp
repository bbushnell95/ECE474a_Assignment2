/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/17/2016
Assignment: 2
File: Output.cpp
Description: output Class for dpgen program
*/

#include "DatapathComponent.h"

DatapathComponent::DatapathComponent()
{
	name = "Unknown";
	dataWidth = 0;
	visited = 'w';
}

DatapathComponent::DatapathComponent(std::string n, std::vector<DataType*> _inputs, std::vector<DataType*> _outputs)
{
	name = n;
	_componentInputs = _inputs;
	_componentOutputs = _outputs;
	dataWidth = 0;
	delay = 0;
	visited = 'w';

}

std::string DatapathComponent::getName()
{
	return name;
}

void DatapathComponent::setName(std::string n)
{
	name = n;
}

std::vector<DataType*> DatapathComponent::getInputs()
{
	return _componentInputs;
}

void DatapathComponent::setInputs(std::vector<DataType*> _inputs)
{
	_componentInputs = _inputs;
}

std::vector<DataType*> DatapathComponent::getOutputs()
{
	return _componentOutputs;
}

void DatapathComponent::setOutputs(std::vector<DataType*> _outputs)
{
	_componentOutputs = _outputs;
}

int DatapathComponent::getDataWidth()
{
	return dataWidth;
}

void DatapathComponent::setDataWidth(int dW)
{
	dataWidth = dW;
}

double DatapathComponent::getDelay()
{
	return delay;
}

void DatapathComponent::setDelay(int d)
{
	delay = d;
}

char DatapathComponent::getVisted()
{
	return visited;
}

void DatapathComponent::setVisted(char v)
{
	visited = v;
}

void DatapathComponent::addInput(DataType* newInput)
{
	_componentInputs.push_back(newInput);
}

void DatapathComponent::addOutput(DataType* newOutput)
{
	_componentOutputs.push_back(newOutput);
}

void DatapathComponent::checkIfSigned()
{
	int countSigned = 0;
	int i = 0;

	/* Counts the number of signed variables. */
	for (i = 0; i < (int)_componentInputs.size(); ++i) {
		if ((*_componentInputs.at(i)).getSignUnsigned()) {
			++countSigned;
		}
	}

	/* Change the name for components that have signed versions. */
	if (countSigned == (int)_componentInputs.size()) {
		if ((name == "COMP_lt")
			|| (name == "COMP_gt")
			|| (name == "COMP_eq")
			|| (name == "DIV")
			|| (name == "MOD")
			|| (name == "SHR")) {
			name.insert(0, "S");
		}
	}

}

void DatapathComponent::determineDataWidth()
{
	int i = 0;
	int largestDW = -99;

	/* This will determine what the datawidth of the component is. */
	if ((name == "COMP_lt")
		|| (name == "SCOMP_lt")
		|| (name == "COMP_gt")
		|| (name == "SCOMP_gt")
		|| (name == "COMP_eq")
		|| (name == "SCOMP_eq")) {
		for (i = 0; i < 2; i++) {
			if ((*_componentInputs.at(i)).getDataWidth() > largestDW) {
				largestDW = (*_componentInputs.at(i)).getDataWidth();
			}
		}
		dataWidth = largestDW;
	}
	else {
		dataWidth = (*_componentOutputs.at(0)).getDataWidth();
	}
}

void DatapathComponent::assignDelay()
{
	/* This is the provided delays of each datapath component with specific widths. */
	double delayTimes[12][6] = { {2.616, 2.644, 2.879, 3.061, 3.602, 3.966},
								 {2.704, 3.713, 4.924, 5.638, 7.270, 9.566},
								 {3.024, 3.412, 4.890, 5.569, 7.253, 9.566},
	                             {2.438, 3.651, 7.453, 7.811, 12.395, 15.354},
								 {3.031, 3.934, 5.949, 6.256, 7.264, 8.416},
								 {4.083, 4.115, 4.815, 5.623, 8.079, 8.766},
								 {3.644, 4.007, 5.178, 6.460, 8.819, 11.095},
								 {3.614, 3.980, 5.152, 6.549, 8.565, 11.220},
								 {0.619, 2.144, 15.439, 33.093, 86.312, 243.233},
								 {0.758, 2.149, 16.078, 35.563, 88.142, 250.583},
								 {1.792, 2.218, 3.111, 3.471, 4.347, 6.200},
								 {1.792, 2.218, 3.108, 3.701, 4.685, 6.503}};

	/* Assigns a delay to the datapath component based on type and width. */
	if (!name.compare("REG")) {
		switch (dataWidth){
			case 1: delay = delayTimes[0][0];
				break;
			case 2: delay = delayTimes[0][1];
				break;
			case 8: delay = delayTimes[0][2];
				break;
			case 16: delay = delayTimes[0][3];
				break;
			case 32: delay = delayTimes[0][4];
				break;
			case 64: delay = delayTimes[0][5];
		}
	}
	if (!name.compare("ADD")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[1][0];
			break;
		case 2: delay = delayTimes[1][1];
			break;
		case 8: delay = delayTimes[1][2];
			break;
		case 16: delay = delayTimes[1][3];
			break;
		case 32: delay = delayTimes[1][4];
			break;
		case 64: delay = delayTimes[1][5];
		}
	}
	if (!name.compare("SUB")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[2][0];
			break;
		case 2: delay = delayTimes[2][1];
			break;
		case 8: delay = delayTimes[2][2];
			break;
		case 16: delay = delayTimes[2][3];
			break;
		case 32: delay = delayTimes[2][4];
			break;
		case 64: delay = delayTimes[2][5];
		}
	}
	if (!name.compare("MUL")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[3][0];
			break;
		case 2: delay = delayTimes[3][1];
			break;
		case 8: delay = delayTimes[3][2];
			break;
		case 16: delay = delayTimes[3][3];
			break;
		case 32: delay = delayTimes[3][4];
			break;
		case 64: delay = delayTimes[3][5];
		}
	}
	if (!name.compare("COMP_lt") || !name.compare("COMP_eq") || !name.compare("COMP_gt")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[4][0];
			break;
		case 2: delay = delayTimes[4][1];
			break;
		case 8: delay = delayTimes[4][2];
			break;
		case 16: delay = delayTimes[4][3];
			break;
		case 32: delay = delayTimes[4][4];
			break;
		case 64: delay = delayTimes[4][5];
		}
	}
	if (!name.compare("MUX2x1")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[5][0];
			break;
		case 2: delay = delayTimes[5][1];
			break;
		case 8: delay = delayTimes[5][2];
			break;
		case 16: delay = delayTimes[5][3];
			break;
		case 32: delay = delayTimes[5][4];
			break;
		case 64: delay = delayTimes[5][5];
		}
	}
	if (!name.compare("SHR")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[6][0];
			break;
		case 2: delay = delayTimes[6][1];
			break;
		case 8: delay = delayTimes[6][2];
			break;
		case 16: delay = delayTimes[6][3];
			break;
		case 32: delay = delayTimes[6][4];
			break;
		case 64: delay = delayTimes[6][5];
		}
	}
	if (!name.compare("SHL")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[7][0];
			break;
		case 2: delay = delayTimes[7][1];
			break;
		case 8: delay = delayTimes[7][2];
			break;
		case 16: delay = delayTimes[7][3];
			break;
		case 32: delay = delayTimes[7][4];
			break;
		case 64: delay = delayTimes[7][5];
		}
	}
	if (!name.compare("DIV")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[8][0];
			break;
		case 2: delay = delayTimes[8][1];
			break;
		case 8: delay = delayTimes[8][2];
			break;
		case 16: delay = delayTimes[8][3];
			break;
		case 32: delay = delayTimes[8][4];
			break;
		case 64: delay = delayTimes[8][5];
		}
	}
	if (!name.compare("MOD")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[9][0];
			break;
		case 2: delay = delayTimes[9][1];
			break;
		case 8: delay = delayTimes[9][2];
			break;
		case 16: delay = delayTimes[9][3];
			break;
		case 32: delay = delayTimes[9][4];
			break;
		case 64: delay = delayTimes[9][5];
		}
	}
	if (!name.compare("INC")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[10][0];
			break;
		case 2: delay = delayTimes[10][1];
			break;
		case 8: delay = delayTimes[10][2];
			break;
		case 16: delay = delayTimes[10][3];
			break;
		case 32: delay = delayTimes[10][4];
			break;
		case 64: delay = delayTimes[10][5];
		}
	}
	if (!name.compare("DEC")) {
		switch (dataWidth) {
		case 1: delay = delayTimes[11][0];
			break;
		case 2: delay = delayTimes[11][1];
			break;
		case 8: delay = delayTimes[11][2];
			break;
		case 16: delay = delayTimes[11][3];
			break;
		case 32: delay = delayTimes[11][4];
			break;
		case 64: delay = delayTimes[11][5];
		}
	}
}
