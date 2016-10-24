#include<string>
#include<vector>
#include<cstring>
#include<algorithm>

class DataType {
protected:
	std::string name;
	int dataWidth;
	bool signUnsigned; //used to see if variable is singed or unsigned (1 signed, 0 unsigned)

public:
	/*Methods*/
	std::string getName();
	void setName(std::string n);
	int getDataWidth();
	void setDataWidth(int dW);
};
