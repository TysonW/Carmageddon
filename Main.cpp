#include <string>
#include <iostream>
#include <time.h>
#include "unistd.h"
#include "pigpio.h"
#include <opencv2/opencv.hpp>
#include "Track.h"
#include "Comm.h"

int main(){
	Comm go;
	go.Menu();
	return 0; //Exit executable file
}
