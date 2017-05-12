#include <string> //string
#include <iostream> //input and output
#include <time.h> 
#include "Motor.h" //Motor class
#include "Track.h" //Track class

typedef std::chrono::duration<int, std::ratio<1, 40>> frame_duration;

class Comm
{
	private:
	CMotor go; //Create an object from the class CMotor
	std::string CMD; //Command variable

	
	public:
		Comm();
		~Comm();
		int Menu();
		int ManDir(); //Manual Direction
		int AutoDir(); //Autonmous Direction
		
		//multi-threading
		bool _thread_exit = 0;
		static void menu_thread(Comm* ptr);
		//to call the thread for Menu()
		void CommStart();
	
		
};
