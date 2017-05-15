 #include "BufferToggle.h"
 
 BufferToggle::BufferToggle(){}
 BufferToggle::~BufferToggle(){}
 
void BufferToggle::off(void)
{
	tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}


        /*
         * Enables buffered input
         */

void BufferToggle::on(void)
{
	tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
	t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}
