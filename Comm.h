#include <string> //string
#include <iostream> //input and output
#include "Motor.h" //Motor class

class Comm: public CMotor
{
	private:
	CMotor go; //Create an object from the class CMotor
	std::string CMD; //Command variable
	public:
		Comm();
		~Comm();
		int Menu();
		int ManDir(); //Manual Direction
		int AutoDir(); //Autonmous Direction
		
};
