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
