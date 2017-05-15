#include <vector>
#include <thread>
#include <opencv2/opencv.hpp>

class Track
{
private:
	double start_tic;  //start time 
	double stop_tic;  //stop time
	double freq;	//freq of the system
	double elapsed_time; //time passed (fps)

	cv::VideoCapture vid; //creates the vid object for video capture
	cv::Mat canvas;
	cv::Mat RedMat;	//storing matrix for red
	cv::Mat GreenMat;	//storing matrix for green
	cv::Mat HSV;	//image after converting to HSV format
	cv::Mat mask;	//mask apply to the image
	cv::Mat erode;	//image after erode
	cv::Mat dilate; //image after dilate

	cv::Rect rr; //box drawn around the ball
	cv::Rect rg; //box drawn around the ball
	
	//multi-threading
	bool _thread_exit = 0; // thread safe?
	static void update_thread(Track* ptr);
	static void draw_thread(Track* ptr);

	int distR = 0; //distance of Red object from camera
	int distG = 0; //distance of Green object from camera

	int GreenCenter = 0;
	int RedCenter = 0;
public:

	/** @brief Constructor
	* @param N/A
	* @return N/A
	*/
	Track();

	/** @brief Destructor
	* @param N/A
	* @return N/A
	*/
	~Track();

	/** @brief Record & process the webcam image and determine the location of the colored object.
	*			Also, send the servo motor commands to orient the pan/tilt system to center the object in the field of view
	* @param N/A
	* @return N/A
	*/
	void update();

	/** @brief Display the processed image
	* @param matrix of the image wanted to display
	* @return N/A
	*/
	void draw();

	/** @brief Start the colour tracking
	* @param matrix of the image wanted to display
	* @return N/A
	*/
	void start();
	
	//Test the Trackin
	void TestCam();
	
	//Check Distance of each colour
	int CheckRed();
	int CheckGreen();
	
	//Check Center Point of each colour
	int Check_R_Cent();
	int Check_G_Cent();
	
	//variables to store old distance
	int oldG;
	int oldR;
};
