#include "Register.h"

Register::Register()
{
	name = "Unknown";
	signUnsigned = false;
	dataWidth = 0;
}

Register::Register(std::string n, bool s, int dW)
{
	name = n;
	signUnsigned = s;
	dataWidth = dW;
}
