#include "Comm.h"

#define Speed 100

Comm::Comm(){}
Comm::~Comm(){}

int Comm::Menu()
{
	go.MotorInitialise(); //Initialize the pinout for the Motor

	std::cout << "Welcome to the menu" <<  std::endl;
	
	while (CMD != "l") //lower case L
	{
		std::cout << "Press 'e' for Autonomous Mode " << std::endl;
		std::cout << "Press 'r' for Manual Mode" << std::endl;
		std::cout << "Press 'l' to leave" << std::endl;
	
		//User chooses either 'e' or 'r'
		std::cin >> CMD; //Have to press enter to receive the command
	
		if (CMD == "e"){std::cout << "hi" << std::endl;}	//Autonomous mode
		else if (CMD == "r"){ManDir();}						//Manual Mode
	}
	return 0; //exit the Menu function
}

int Comm :: ManDir()
{
	std::cout << "Which Direction" <<std::endl;
	std::cin >> CMD; //Ask the input for which direction
	
	while(CMD != "q")//If q is pressed, leave the Manual Direction Function
	{
		if (CMD == "w")
		{
			go.FORWARD(Speed);
			std::cout << "Forward" << std::endl;
			std::cout << "Next Direction" << std::endl;
			std::cin >> CMD; //Ask the input for which direction
		}
			
		else if (CMD == "a")
		{
			go.LEFT(Speed);
			std::cout << "Next Direction" << std::endl;
			std::cin >> CMD; //Ask the input for which direction
		}
		
		else if (CMD == "s")
		{
			go.BACKWARD(Speed);
			std::cout << "Next Direction" << std::endl;
			std::cin >> CMD; //Ask the input for which direction
		}
		
		else if (CMD == "d")
		{
			go.RIGHT(Speed);
			std::cout << "Next Direction" << std::endl;
			std::cin >> CMD; //Ask the input for which direction
		}
		
		else if (CMD == "x")
		{
			go.STOP();
			std::cout << "Next Direction" << std::endl;
			std::cin >> CMD; //Ask the input for which direction
		}
		
		else if (CMD == "t")
		{
			go.Test();
			std::cout << "Next Direction" << std::endl;
			std::cin >> CMD; //Ask the input for which direction
		}	
	}
	go.STOP(); //Stop the motor
	return 0;
}


