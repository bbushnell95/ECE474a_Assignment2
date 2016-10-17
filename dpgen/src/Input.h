/*
Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
Date Create: 10/17/2016
Assignment: 2
File: Input.h
Description: input Class for dpgen program
*/

#ifndef INPUT_H
#define INPUT_H

#include<string>
#include<vector>
#include<cstring>
#include<algorithm>


class Input {

private:
	std::string name;
	int dataWidth;
public:
	/*construsctors*/
	Input();
	Input(std::string n, int dW);

	/*Methods*/
	std::string getName();
	void setName(std::string n);
	int getDataWidth();
	void setDataWidth(int dW);
};



#endif //INPUT_H