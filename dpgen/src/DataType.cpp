#include "DataType.h"

std::string DataType::getName()
{
	return name;
}

void DataType::setName(std::string n)
{
	name = n;
}

int DataType::getDataWidth()
{
	return dataWidth;
}

void DataType::setDataWidth(int dW)
{
	dataWidth = dW;
}

bool DataType::getSignUnsigned()
{
	return signUnsigned;
}

void DataType::setSignUnsiged(bool sU)
{
	signUnsigned = sU;
}

std::vector<DatapathComponent> DataType::getGoingTo()
{
	return goingTo;
}

void DataType::setGoingTo(std::vector<DatapathComponent> gT)
{
	goingTo = gT;
}

std::vector<DatapathComponent> DataType::getComingFrom()
{
	return comingFrom;
}

void DataType::setComingFrom(std::vector<DatapathComponent> cF)
{
	comingFrom = cF;
}

void DataType::addToGoingTo(DatapathComponent newComponent)
{
	goingTo.push_back(newComponent);
}

void DataType::addToComingFrom(DatapathComponent newComponent)
{
	comingFrom.push_back(newComponent);
}

