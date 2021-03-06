/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/17/2016
Assignment: 2
File: Output.h
Description: output Class for dpgen program
*/

#ifndef WIRE_H
#define WIRE_H

#include<string>
#include<vector>
#include<cstring>
#include<algorithm>
#include"DataType.h"


class Wire: public DataType{

//private:
	//	std::string name;
	//	bool sign;
	//	int dataWidth;

public:
	/*constructors*/
	Wire();
	Wire(std::string n, bool s, int dW);

	/*Methods*/
	/*std::string getName();
	void setName(std::string n);
	int getDataWidth();
	void setDataWidth(int dW);*/
};

#endif // WIRE_H
