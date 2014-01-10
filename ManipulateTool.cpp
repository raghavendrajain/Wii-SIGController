#include "ControllerEvent.h"
#include "Controller.h"
#include "Logger.h"
#include <iostream>
// #include <boost/python.hpp>
// #include <Python.h>
// #include <dlfcn.h>

#define PI 3.141592      
#define DEG2RAD(DEG) ( (PI) * (DEG) / 180.0 )


// namespace py = boost::python; // create namespace variable for boost::python
using namespace std;

// std::string parse_python_exception(); // functional declaration for exception handling

// template <typename T> string tostr(const T& t) { ostringstream os; os<<t; return os.str(); } // template to convert double variables to string




  
class MyController : public Controller {  
public:  
  void onInit(InitEvent &evt);  
  double onAction(ActionEvent&);
  void onRecvMsg(RecvMsgEvent &evt); 
  void onCollision(CollisionEvent &evt);   
 


private:
  bool accelerationValueRecieved;
 
};  

static double roll  = 0; 
static double pitch = 0; 
static double yaw   = 0; 

static double xAcc = 0; 
static double yAcc = 0; 
static double zAcc = 0; 


static int messageCount;

static int onActionCount;

static int flag=1;

static Vector3d pos;



  
void MyController::onInit(InitEvent &evt) {  

  SimObj *obj = getObj(myname());
 
}  
  
double MyController::onAction(ActionEvent &evt) {  
  //return 1.0;
  SimObj *obj = getObj(myname());
 
 



return 0.00001;
      
} 

  std::string msg = " ";

  void MyController::onRecvMsg(RecvMsgEvent &evt)
{

  SimObj *my = getObj(myname());



  char *all_msg = (char*)evt.getMsg();
  // std::string msg;
  msg= evt.getMsg();


  char roll_angle[10]=" "; 
  char pitch_angle[10]=" ";
  char yaw_angle[10]=" ";


  char x_accl[10]=" "; 
  char y_accl[10]=" ";
  char z_accl[10]=" ";




  int result=0;

  result = sscanf(msg.c_str(), "%[^','],%[^','],%[^','],%[^','],%[^','],%[^',']", roll_angle, pitch_angle, yaw_angle,x_accl,y_accl,z_accl ); 

  
  
  roll = atof(roll_angle);
  pitch = atof(pitch_angle);
  yaw = atof(yaw_angle);

  xAcc=atof(x_accl);
  yAcc=atof(y_accl);
  zAcc=atof(z_accl);



  LOG_MSG((" Roll, pitch, yaw angles are x,y,z acceleration data of wii are : %f %f %f %f %f %f ", roll, pitch, yaw, xAcc, yAcc, zAcc ));
  // std::cout <<"roll angle is" << roll * PI/180 <<std::endl;

  my->setDynamicsMode(false);

  // This is used for moving tool according to roll angle obtained from wii movement.
  my->setAxisAndAngle(1.0, 0.0, 0.0, -roll * PI/180);  
  
  // This is used for moving tool according to pitch angle obtained from wii movement. 
  // my->setAxisAndAngle(0.0, 0.0, 1.0, pitch * PI/180);  

 





  messageCount++;
  std::cout << "The mesage count is" << messageCount <<std::endl;

  //my->setPosition(pos.x(), pos.y(), pos.z() - yPos);

}


  
 

void MyController::onCollision(CollisionEvent &evt) { 
}


extern "C" Controller * createController() {  
  return new MyController;  
}  


