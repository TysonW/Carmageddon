#include <string> //string
#include <iostream> //input and output
#include <time.h> 
#include "Motor.h" //Motor class
#include "Track.h" //Track class
#include "BufferToggle.h"




class Comm
{
	private:
	
	public:
	CMotor go; //Create an object from the class CMotor

	//BufferToggle object called bt to toggle buffer on or off
	BufferToggle bt;
	Track cam;
	//green right turn, reg left turn
	int Green_Dist = 0; //distance to green tag
	int Red_Dist = 0; //distance to red tag

	std::string CMD; //Command variable
	
		Comm();
		~Comm();
		int Menu();
		int ManDir(); //Manual Direction
		int AutoDir(); //Autonmous Direction
		
		//int oldG;
		int oldG = 0;
		int oldR = 0;

};
