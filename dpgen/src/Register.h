#ifndef REGISTER_H
#define REGISTER_H

#include<string>
#include<vector>
#include<cstring>
#include<algorithm>
#include "DataType.h"


class Register : public DataType {

	//private:
	//	std::string name;
	//	bool sign;
	//	int dataWidth;
public:
	/*Constructors*/
	Register();
	Register(std::string n, bool s, int dW);

	/*Methods*/
	//std::string getName();
	//void setName(std::string n);
	//int getDataWidth();
	//void setDataWidth(int dW);
};

#endif //REGISTER_H