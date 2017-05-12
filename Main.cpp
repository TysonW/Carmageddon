#include <string>
#include <iostream>
#include <time.h>
#include "unistd.h"
#include "pigpio.h"
#include <opencv2/opencv.hpp>
#include "Comm.h"

int main(int argc, char** argv){
	Comm go;
	Track cam;
	
	cam.start();
	
	go.Menu();	
	return 0; //Exit executable file
}

