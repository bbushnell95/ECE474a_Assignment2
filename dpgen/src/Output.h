/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/17/2016
Assignment: 2
File: Output.h
Description: output Class for dpgen program
*/

#ifndef OUTPUT_H
#define OUTPUT_H

#include<string>
#include<vector>
#include<cstring>
#include<algorithm>


class Output {

private:
	std::string name;
	int dataWidth;
public:
	/*construsctors*/
	Output();
	Output(std::string n, int dW);

	/*Methods*/
	std::string getName();
	void setName(std::string n);
	int getDataWidth();
	void setDataWidth(int dW);
};



#endif //OUTPUT_H