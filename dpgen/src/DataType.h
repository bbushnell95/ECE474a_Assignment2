#ifndef DATATYPE_H
#define DATATYPE_H

#include<string>
#include<vector>
#include<cstring>
#include<algorithm>
//#include"DatapathComponent.h"

class DatapathComponent;

class DataType {
protected:
	std::string name;
	int dataWidth;
	bool signUnsigned; //used to see if variable is singed or unsigned (1 signed, 0 unsigned)
	std::vector<DatapathComponent*> comingFrom;
	std::vector<DatapathComponent*> goingTo;

public:
	/*Methods*/
	std::string getName();
	void setName(std::string n);
	int getDataWidth();
	void setDataWidth(int dW);
	bool getSignUnsigned();
	void setSignUnsiged(bool sU);
	std::vector<DatapathComponent*> getGoingTo();
	void setGoingTo(std::vector<DatapathComponent*> gT);
	std::vector<DatapathComponent*> getComingFrom();
	void setComingFrom(std::vector<DatapathComponent*> cF);
	void addToGoingTo(DatapathComponent* newComponent);
	void addToComingFrom(DatapathComponent* newComponent);

};
#endif 