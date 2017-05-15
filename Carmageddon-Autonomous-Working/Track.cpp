#include "Track.h"

#include <iomanip>
#include <iostream>

#define HEIGHT	19 //in mm
#define FOCAL	2.3//in mm
#define MEGAPIX	0.002903 //in mm

#define fspX 400 //x positon of fsp
#define fspY 450 //y positon of fsp
#define fontsize_fps 2 //size of the font for displaying fps 

#define erodeSize cv::Size(3,3) //size of pixel to erode x,y
#define dilateSize cv::Size(15, 15) //size of pixel to dilate x,y

#define erodeElement cv::getStructuringElement(cv::MORPH_RECT,erodeSize)
#define dilateElement cv::getStructuringElement(cv::MORPH_RECT,dilateSize)

#define RED cv::Scalar(0, 0, 255) //colour blue in RGB formate -> (Blue, Green, Red)
#define RED_lower_bound cv::Scalar{ 147, 151, 184 } //colour blue lower bound in hsv formate
#define RED_upper_bound cv::Scalar{ 233, 212, 256 } //colour blue upper bound in hsv formate

#define GREEN cv::Scalar(0, 255, 0) //colour blue in RGB formate -> (Blue, Green, Red)
#define GREEN_lower_bound cv::Scalar{ 32, 102, 100 } //colour blue lower bound in hsv formate
#define GREEN_upper_bound cv::Scalar{ 88, 181, 212 } //colour blue upper bound in hsv formate

#define White cv::Scalar(255, 255, 255) //colour blue in RGB formate -> (Blue, Green, Red)

typedef std::chrono::duration<int, std::ratio<1, 40>> frame_duration;

#define WIN4618
using namespace std;

Track::Track()
{
#ifdef WIN4618
	//0 inside argument is webcam, 2 inside argument is external cam
	vid.open(0);
	
#endif

#ifdef PI4618
	//open external cam
	vid.open(0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
#endif 
	//Servo starting poistion
	//Control.set_data(Servo, Motor_UpDown, MotorY); 
	//Control.set_data(Servo, Motor_LeftRight, MotorX);
}


Track::~Track()
{
}

void Track::update()
{
	//get frequency
	freq = cv::getTickFrequency();
	//start clock
	start_tic = cv::getTickCount();
	
	vid >> canvas;
	
	//convert to HSV
	cv::cvtColor(canvas, HSV, cv::COLOR_BGR2HSV);

	//appy mask
	cv::inRange(HSV, RED_lower_bound, RED_upper_bound, RedMat);
	cv::inRange(HSV, GREEN_lower_bound, GREEN_upper_bound, GreenMat);

	//kernel for erode
	//cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT, erodeSize);
	//kernel for erode
	//cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT, dilateSize);

	//erode then dilate
	cv::erode(RedMat, RedMat, erodeElement);
	cv::dilate(RedMat, RedMat, dilateElement);
	cv::erode(GreenMat, GreenMat, erodeElement);
	cv::dilate(GreenMat, GreenMat, dilateElement);

	//find the shape of the object
	vector<cv::Vec4i> hierarchy;
	vector<vector<cv::Point>> contoursRED;
	vector<vector<cv::Point>> contoursGREEN;

	findContours(RedMat, contoursRED, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	findContours(GreenMat, contoursGREEN, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	oldR = distR;
	//draw a box around the shape, find the middle and follow it 
	for (unsigned int i = 0; i < contoursRED.size(); i++)
	{
		rr = cv::boundingRect(contoursRED.at(i));
		distR = rr.height * rr.width;
		
		//if distance is the same from previous
		if (distR == oldR){distR = 0;} 
		
 		//distR = FOCAL * HEIGHT / (MEGAPIX * r.height);
		//RedCenter = r.x + (r.width / 2); 
		//std::cout << "RED: " << distR << std::endl;
		cv::rectangle(canvas, rr, RED, 3);
	}

	 oldG = distG;
	//draw a box around the shape, find the middle and follow it 
	for (unsigned int i = 0; i < contoursGREEN.size(); i++)
	{
		rg = cv::boundingRect(contoursGREEN.at(i));
		distG = rg.height * rg.width;
		
		//if distance is the same from previous
		if (distG == oldG){distG = 0;} 
		
		//distG = FOCAL * HEIGHT / (MEGAPIX * r.height);
		//GreenCenter = r.x + (r.width / 2);
		//std::cout << "GREEN: " << distG << std::endl; 
		cv::rectangle(canvas, rg, GREEN, 3);
	}
	
	//std::cout << "Size of width of Matrix: " << canvas.cols << std::endl;

	//stop clock
	stop_tic = cv::getTickCount();

	//calculates fps
	elapsed_time = (freq / (stop_tic - start_tic));
}

void Track::draw()
{
	while(canvas.empty())
	{
		//display fsp on canvas
		//string fsp = to_string(elapsed_time);
		//cv::putText(canvas, fsp, cv::Point(fspX, fspY), cv::FONT_HERSHEY_COMPLEX_SMALL, fontsize_fps, White, 1);
	}
		//display canvas
		//cv::imshow("Image", canvas);

		//cv::waitKey(1);
}


void Track::start()
{
	update();
	//std::thread t2(&Track::draw_thread,this);

	//t2.join();

}

void Track::update_thread(Track* ptr)
{
	while (ptr->_thread_exit == false)
	{
		cv::waitKey(100);
		ptr->update();
	}
}

void Track::draw_thread(Track* ptr)
{
	while (ptr->_thread_exit == false)
	{
		cv::waitKey(100);
		ptr->draw();
	}
}
void Track::TestCam()
{
	do{
		update();
		draw();
	}while(cv::waitKey(10) != ' ');

		
}

int Track::CheckGreen(void)
{
	return distG; //distance of Green object from camera
}
int Track::CheckRed(void)
{
	return distR; //distance of Red object from camera
}

int Track::Check_R_Cent(void)
{
	return RedCenter;
}
int Track::Check_G_Cent(void)
{	
	return GreenCenter;
	
}

