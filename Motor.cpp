#include "Motor.h"

//     Motor  Pi gpio
#define AIN1     16
#define AIN2     20
#define BIN1     13
#define BIN2     6
#define PWMA     21
#define PWMB     5

//Motor speed settings
#define FAST   160
#define MEDIUM 100
#define SLOW   50
#define PAUSE  0

CMotor::CMotor(){if (gpioInitialise() < 0) {exit(1);}}
CMotor::~CMotor(){
	gpioTerminate(); //Terminates library
	}


void CMotor::Test()
   {
		
	
		int i = 0;
		while(i < 30)
		{
			FORWARD(SLOW);
			sleep(5);   
			
			FORWARD(FAST);
			sleep(5);
			i++;
		}
		
		gpioTerminate();
   }


void CMotor::MotorInitialise()
{
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

void CMotor::FORWARD(int spd)
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

void CMotor::BACKWARD(int spd)
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

void CMotor::STOP()
{
	//set motor A and B speed to zero
	gpioPWM(PWMA,PAUSE);
	gpioPWM(PWMB,PAUSE);
}

void CMotor:: LEFT(int spd)
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
void CMotor::RIGHT(int spd)
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
