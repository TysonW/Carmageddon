#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h> //exit
#include <stdio.h> //sleep
#include <stdint.h>

class CMotor  
{
	private:
	public:
		CMotor();
		~CMotor();	
		//Initialize GPIO
		void MotorInitialise();
		//Move forward
		void FORWARD(int spd);
		//Move backward
		void BACKWARD(int spd);
		//Stop the motor
		void STOP();
		//Turn Left
		void LEFT(int spd);
		//Turn Right
		void RIGHT(int spd);
		//Test Motors
		void Test();
};
