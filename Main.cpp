#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//     Motor  Pi gpio
#define AIN1     5
#define AIN2     6
#define BIN1     19
#define BIN2     26
#define PWMA     7
#define PWMB     8

//Motor speed settings
#define FAST   160
#define MEDIUM 100
#define SLOW   50


int main()
   {
		if (gpioInitialise() < 0) {exit(1);}	   //intialize the gpio
		
		//initialise motor A outputs
		gpioSetMode(AIN1, PI_OUTPUT);
		gpioSetMode(AIN2, PI_OUTPUT);
		
		//initialise motor B outputs
		gpioSetMode(BIN1, PI_OUTPUT);
		gpioSetMode(BIN2, PI_OUTPUT);
		
		//initialise motors A and B speed control
		gpioSetMode(PWMA, PI_OUTPUT);
		gpioSetMode(PWMB, PI_OUTPUT);
		
		gpioPWM(PWMA,0);
		gpioPWM(PWMB,0);
		
		

		while(i < 100)
		{
			gpioWrite(3, PI_HIGH);     
			gpioDelay(5000000);
			gpioWrite(3,PI_LOW);      
			i++;
		}
		
		gpioTerminate();
   }


void MotorInitialise()
{
	
	
}

void FORWARD(int spd)
{
	//set motor A to FWD
	gpioWrite(AIN1, PI_HIGH);
	gpioWrite(AIN2, PI_LOW);
	
	//set motor B to FWD
	gpioWrite(BIN1, PI_HIGH);
	gpioWrite(BIN2, PI_HIGH);
	
	//set motor A and B to specified speed
	gpioPWM(PWMA,spd);
	gpioPWM(PWMB,spd);
	
	
	
}

void BACKWARD()
{
}

void STOP()
{
}

void LEFT()
{
}

void RIGHT()
{
}


