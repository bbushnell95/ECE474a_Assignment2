/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/17/2016
Assignment: 2
File: Output.cpp
Description: output Class for dpgen program
*/

#include "Output.h"

Output::Output()
{
	name = "Unknown";
	dataWidth = 0;
}

Output::Output(std::string n, bool s, int dW)
{
	name = n;

	dataWidth = dW;
}

std::string Output::getName()
{
	return name;
}

void Output::setName(std::string n)
{
	name = n;
}

int Output::getDataWidth()
{
	return dataWidth;
}

void Output::setDataWidth(int dW)
{
	dataWidth = dW;
}
