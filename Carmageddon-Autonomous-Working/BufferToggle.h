/*This code was retyped manually from the terminal*/
/* BufferToggle.hpp
 * @Author
 *    Luc Lieber
 *
 *    A simple class to toggle buffered input
 */
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>

class BufferToggle
{
    private:
        struct termios t;

    public:

		BufferToggle();
		~BufferToggle();
	
        /*
         * Disables buffered input
         */
		
        void off(void);
        /*
         * Enables buffered input
         */

        void on(void);

};
