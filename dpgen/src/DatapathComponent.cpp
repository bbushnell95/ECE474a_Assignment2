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
	/* TODO: FINISH THIS */
}

DatapathComponent::DatapathComponent(std::string n, std::vector<DataType> _inputs, std::vector<DataType> _outputs)
{
	name = n;
	_componentInputs = _inputs;
	_componentOutputs = _outputs;

}

std::string DatapathComponent::getName()
{
	return name;
}

void DatapathComponent::setName(std::string n)
{
	name = n;
}

std::vector<DataType> DatapathComponent::getInputs()
{
	return _componentInputs;
}

void DatapathComponent::setInputs(std::vector<DataType> _inputs)
{
	_componentInputs = _inputs;
}

std::vector<DataType> DatapathComponent::getOutputs()
{
	return _componentOutputs;
}

void DatapathComponent::setOutputs(std::vector<DataType> _outputs)
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

int DatapathComponent::getDelay()
{
	return delay;
}

void DatapathComponent::setDelay(int d)
{
	delay = d;
}

void DatapathComponent::addInput(DataType newInput)
{
	_componentInputs.push_back(newInput);
}

void DatapathComponent::addOutput(DataType newOutput)
{
	_componentOutputs.push_back(newOutput);
}
