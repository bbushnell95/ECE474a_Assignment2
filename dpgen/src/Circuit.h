/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/3/2016
Assignment: 2
File: Circuit.h
Description: Circuit Class for dpgen program
*/

#ifndef CIRCUIT_H
#define CIRCUIT_H


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>
#include<algorithm>

#include "DatapathComponent.h"


class Circuit {

private:
	std::string outputCircuit;
	double criticalPath;

public:
	/*Constructors*/
	Circuit();

	/*Getters and Setters*/
	double getCriticalPath();
	void setCriticalPath(double cp);

	/*Methods*/
	bool readFile(char* fileName);
	void writeToFile(char* fileName);
	void determineCriticalPath();


};










#endif //CIRCUIT_H