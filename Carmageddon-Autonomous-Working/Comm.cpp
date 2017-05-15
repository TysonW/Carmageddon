#include "Comm.h"
#include <thread>
#include <opencv2/opencv.hpp>
#include <cmath>

#define VFAST 100
#define FAST 65
#define MED  50
#define SLOW 40   
#define RIGHTBOUND 350
#define LEFTBOUND 290
#define ADJUST 10
using namespace std;

//initialise cam tracking
Comm::Comm()
{}

Comm::~Comm(){}

int Comm::Menu()
{
	
	
	go.MotorInitialise(); //Initialize the pinout for the Motor

	std::cout << "Welcome to the menu" <<  std::endl;
	bt.off();
	while (CMD != "l") //lower case L
	{
		std::cout << "Press 'e' for Autonomous Mode " << std::endl;
		std::cout << "Press 'r' for Manual Mode" << std::endl;
		std::cout << "Press 'l' to leave" << std::endl;
	
		//User chooses either 'e' or 'r'
		std::cin >> CMD; //Have to press enter to receive the command
	
		if (CMD == "e"){AutoDir();}	//Autonomous mode
		else if (CMD == "r"){ManDir();}						//Manual Mode	
	}
	return 0; //exit the Menu function
}

int Comm :: ManDir()
{
	bt.off();//You don't need to press enter
	std::cout << "Which Direction" <<std::endl;
	
	while(CMD != "q")//If q is pressed, leave the Manual Direction Function
	{
		CMD = std::getchar();
		
		if (CMD == "w")
		{
			go.FORWARD(FAST,FAST);
			std::cout << "Forward" << std::endl;
			std::cout << "Next Direction" << std::endl;
			//std::cin >> CMD; //Ask the input for which direction
			//CMD = getchar();; //Ask the input for which direction
		}
			
		else if (CMD == "a")
		{
			go.LEFT(MED);
			std::cout << "Next Direction" << std::endl;
			//std::cin >> CMD; //Ask the input for which direction
			//CMD = getchar();
		}
		
		else if (CMD == "s")
		{
			go.BACKWARD(SLOW);
			std::cout << "Next Direction" << std::endl;
			//std::cin >> CMD; //Ask the input for which direction
			//CMD = getchar();
		}
		
		else if (CMD == "d")
		{
			go.RIGHT(MED);
			std::cout << "Next Direction" << std::endl;
			//std::cin >> CMD; //Ask the input for which direction
			//CMD = getchar();
		}
		
		else if (CMD == "x")
		{
			go.STOP();
			std::cout << "Next Direction" << std::endl;
			//std::cin >> CMD; //Ask the input for which direction
			//CMD = getchar();
		}
		
		else if (CMD == "t")
		{
			go.Test();
			std::cout << "Next Direction" << std::endl;
			//std::cin >> CMD; //Ask the input for which direction
			//CMD = getchar();
		}	
	
	}

    	go.STOP(); //Stop the motor
	bt.on();//You need to press enter
	return 0;
}



int Comm :: AutoDir()
{
	
	//start with moving forward to get within range

	
	while(1)
	{
		oldG = Green_Dist;
		oldR = Red_Dist;
		cam.update();
		
		//keep moving forward fast
		cout << "first move" <<endl;
		go.FORWARD(FAST,FAST);
		
		cout << "checking green" <<endl;  
		Green_Dist = cam.CheckGreen();
		cout << "checking red" << endl;
		Red_Dist = cam.CheckRed();
		
		std::cout << Green_Dist << std::endl;
		std::cout << Red_Dist << std::endl;
		
		//if Green Distance is greater 10000 
		//and the difference between the old Distance and New Distance
		//is less than 0, you can turn right
		if (Green_Dist >10000 && (abs(oldG - Green_Dist) > 1) )
		{
			go.RIGHT(MED);
			sleep(0.85);
			
			cout << "checking green" <<endl;  
			
			Green_Dist = 0;
			Red_Dist = 0;
			
		} //end green turn 

		if (Red_Dist >10000 && (abs(oldR - Red_Dist) > 1))
		{
			 go.LEFT(MED);
			 usleep(30);
			 go.STOP();
			 
			 Red_Dist = 0;
			Green_Dist = 0;
		} //end red turn
		
	//std::cin >> CMD;	
    	}//end infinite loop
	return 0;

}
