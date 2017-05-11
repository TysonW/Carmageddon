#include <string>
#include <iostream>
#include <time.h>
#include "unistd.h"
#include "pigpio.h"
#include <opencv2/opencv.hpp>
#include "Comm.h"

int main(){
	Comm go;
	Track cam;
	cam.start();
	go.CommStart();	
	return 0; //Exit executable file
}

