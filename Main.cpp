#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h> //exit
#include <stdio.h> //sleep

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
#define STOP   0


int main()
   {
		
		gpioInitialise();
		int i = 0;
		while(i < 30)
		{
			printf("set high\n");
			gpioWrite(3, PI_LOW);
			printf("sleep 5 seconds\n");     
			sleep(5);
			printf("set low\n");
			gpioWrite(3,PI_HIGH);
			printf("sleep 5 seconds\n");  
			sleep(5);  
			printf("iterate\n");    
			i++;
		}
		
		gpioTerminate();
   }


void MotorInitialise()
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
		
}

void FORWARD(int spd)
{
	//set motor A to FWD
	gpioWrite(AIN1, PI_HIGH);
	gpioWrite(AIN2, PI_LOW);
	
	//set motor B to FWD
	gpioWrite(BIN1, PI_HIGH);
	gpioWrite(BIN2, PI_LOW);
	
	//set motor A and B to specified speed
	gpioPWM(PWMA,spd);
	gpioPWM(PWMB,spd);
	
}

void BACKWARD(int spd)
{
	//set motor A to REV
	gpioWrite(AIN2, PI_HIGH);
	gpioWrite(AIN1, PI_LOW);
	
	//set motor B to REV
	gpioWrite(BIN2, PI_HIGH);
	gpioWrite(BIN1, PI_LOW);
	
	//set motor A and B to specified speed
	gpioPWM(PWMA,spd);
	gpioPWM(PWMB,spd);
	
}

void STOP()
{
	//set motor A and B speed to zero
	gpioPWM(PWMA,STOP);
	gpioPWM(PWMB,STOP);
}

void LEFT(int spd)
{
	//set motor A to REV
	gpioWrite(AIN1, PI_LOW);
	gpioWrite(AIN2, PI_HIGH);
	
	//set motor B to FWD
	gpioWrite(BIN1, PI_HIGH);
	gpioWrite(BIN2, PI_LOW);
	
	//set motor A and B to specified speed
	gpioPWM(PWMA,spd);
	gpioPWM(PWMB,spd);
		
}

//Turn the car right on spot (Tank-like)
void RIGHT(int spd)
{
	//set motor A to FWD
	gpioWrite(AIN1, PI_HIGH);
	gpioWrite(AIN2, PI_LOW);
	
	//set motor B to REV
	gpioWrite(BIN1, PI_LOW);
	gpioWrite(BIN2, PI_HIGH);
	
	
	//set motor A and B to specified speed
	gpioPWM(PWMA,spd);
	gpioPWM(PWMB,spd);
	
	
}


