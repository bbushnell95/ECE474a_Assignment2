/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/17/2016
Assignment: 2
File: Input.h
Description: input Class for dpgen program
*/

#include "Input.h"

Input::Input()
{
	name = "Unknown";
	dataWidth = 0;
}

Input::Input(std::string n, int dW)
{
	name = n;
	dataWidth = dW;
}

std::string Input::getName()
{
	return name;
}

void Input::setName(std::string n)
{
	name = n;
}

int Input::getDataWidth()
{
	return dataWidth;
}

void Input::setDataWidth(int dW)
{
	dataWidth = dW;
}
