#include "Track.h"

#include <iomanip>
#include <iostream>


#define fspX 400 //x positon of fsp
#define fspY 450 //y positon of fsp
#define fontsize_fps 2 //size of the font for displaying fps 

#define erodeSize cv::Size(3,3) //size of pixel to erode x,y
#define dilateSize cv::Size(15, 15) //size of pixel to dilate x,y

#define erodeElement cv::getStructuringElement(cv::MORPH_RECT,erodeSize)
#define dilateElement cv::getStructuringElement(cv::MORPH_RECT,dilateSize)

#define RED cv::Scalar(0, 0, 255) //colour blue in RGB formate -> (Blue, Green, Red)
#define RED_lower_bound cv::Scalar{ 99, 139, 62 } //colour blue lower bound in hsv formate
#define RED_upper_bound cv::Scalar{ 117, 255, 197 } //colour blue upper bound in hsv formate

#define GREEN cv::Scalar(0, 255, 0) //colour blue in RGB formate -> (Blue, Green, Red)
#define GREEN_lower_bound cv::Scalar{ 0, 103, 216 } //colour blue lower bound in hsv formate
#define GREEN_upper_bound cv::Scalar{ 35, 162, 255 } //colour blue upper bound in hsv formate

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


	//draw a box around the shape, find the middle and follow it 
	for (unsigned int i = 0; i < contoursRED.size(); i++)
	{
		r = cv::boundingRect(contoursRED.at(i));

		cv::rectangle(canvas, r, RED, 3);
	}

	//draw a box around the shape, find the middle and follow it 
	for (unsigned int i = 0; i < contoursGREEN.size(); i++)
	{
		r = cv::boundingRect(contoursGREEN.at(i));

		cv::rectangle(canvas, r, GREEN, 3);
	}


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
		string fsp = to_string(elapsed_time);
		cv::putText(canvas, fsp, cv::Point(fspX, fspY), cv::FONT_HERSHEY_COMPLEX_SMALL, fontsize_fps, White, 1);
	}
		//display canvas
		cv::imshow("Image", canvas);

		cv::waitKey(1);
}


void Track::start()
{
	std::thread t1(&Track::update_thread,this);
	std::thread t2(&Track::draw_thread,this);
	t1.detach();
	t2.detach();

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


