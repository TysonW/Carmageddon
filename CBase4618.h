#include <opencv2/opencv.hpp>
#include "ControlPi.h"
//#include "opencv.hpp"
//#include "CControl.h"
//#define WIN4618
/**
*
* @brief This class contains a CControl object and opencv canvas object
*
* This class contains two objects: a communication protocol object control and an
* open cv object canvas
*
* @author Tyson Whyte
*
*/
class CBase4618
   {
   public:

      cv::Mat canvas; ///<OpenCV object for visual graphics
#ifdef WIN4618
      CControl Serial; ///<CControl object for com port communication protocol
#endif
       CControlPi Serial; ///<CControl object for com port communication protocol
      
   };

