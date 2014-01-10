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
  // obj->addForce(0,0,-500);


}  
  
double MyController::onAction(ActionEvent &evt) {  
  //return 1.0;
  SimObj *obj = getObj(myname());
 
  double massOfTool;  
  massOfTool = obj->getMass();

  // Rotation r(0.707,0.707,0,0);
  // Rotation r(1,0,0,0);
  // LOG_MSG(("mass of tool : %f ", massOfTool ));
  //if  ( accelerationValueRecieved )
  //LOG_MSG((" Velocity set on Tool onAction() : %f %f %f ", 0.0, 0.0, zVel ));
  //obj->addForce( 0.0,  0.0,  100 * massOfTool * zAcc); // force 5000 [kg · cm / s ^ 2] in the direction of z axis
  //LOG_MSG(("Force Data : (%f %f %f) ", 0.0, 0.0, 100 * massOfTool * zAcc ));
  // obj->setRotation(r);
  // obj->setForce(0,0,-500);
  // obj->addForce(0,0,-100);
  //obj->addForceAtRelPos(0,0,600,1,0,6.0);
  // static Vector3d pos;


  obj->getPosition(pos);
  
 

  // LOG_MSG((" Current Position of Tool : %f %f %f ", pos.x(), pos.y(), pos.z() ));
  //obj->setPosition(pos.x(), pos.y(), pos.z() - yPos);
  // LOG_MSG((" The change in yPos is : %f  ", yPos ));
  // obj->setRotation(r);
  //obj->setAngularVelocity(0.0,0.0,0.0);
  //if (evt.time() > 5)
     //  obj->setVelocity(0,0,10);
   //obj->setPosition(-30,70,25);
   //obj->addForce(0,0,-100);
  // obj->setVelocity( 0.0, 0.0, zVel ) ;
  //obj->setVelocity(0,0,-10);
  //if (evt.time() > 5)
  //obj->setVelocity(0,0,0);


return 0.00001;
      
} 

  std::string msg = " ";

  void MyController::onRecvMsg(RecvMsgEvent &evt)
{

  SimObj *my = getObj(myname());



  char *all_msg = (char*)evt.getMsg();
  // std::string msg;
  msg= evt.getMsg();

  LOG_MSG((" Position Received by Controller"));

  LOG_MSG((msg.c_str()));




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



  LOG_MSG((" Orientation data received by the Controller : %f %f %f %f %f %f ", roll, pitch, yaw, xAcc, yAcc, zAcc ));
  std::cout <<"roll angle is" << roll <<std::endl;

  my->setDynamicsMode(false);

  // This is used for moving tool according to roll angle obtained from wii movement.
  my->setAxisAndAngle(1.0, 0.0, 0.0, -roll * PI/180);  
  
  // This is used for moving tool according to pitch angle obtained from wii movement. 
  //my->setAxisAndAngle(0.0, 0.0, 1.0, pitch * PI/180);  



  messageCount++;
  std::cout << "The mesage count is" << messageCount <<std::endl;

  //my->setPosition(pos.x(), pos.y(), pos.z() - yPos);

}


  
// void MyController::onRecvMsg(RecvMsgEvent &evt) {  

//   SimObj *my = getObj(myname());  

//   std::string msg = evt.getMsg();  
//   //LOG_MSG(("message received by tool controller onRecvMesg() : %s", msg.c_str()));  
  

//   //  char xAccStr[10], yAccStr[10], zAccStr[10];
 
//   //int result;
  
    
//   //result = sscanf(msg.c_str(), "%[^','],%[^','],%[^',']", xAccStr, yAccStr, zAccStr ); 
//   //xAcc = atof(xAccStr);
//   //yAcc = atof(yAccStr);
//   //zAcc = atof(zAccStr);


//     char xVelStr[10], yVelStr[10], zVelStr[10];

//     int result;


//     result = sscanf(msg.c_str(), "%[^','],%[^','],%[^',']", xVelStr, yVelStr, zVelStr );
//     xVel = atof(xVelStr);
//     yVel = atof(yVelStr);
//     zVel = atof(zVelStr);

  
 


//   //accelerationValueRecieved =true;

// }  

void MyController::onCollision(CollisionEvent &evt) { 
}


extern "C" Controller * createController() {  
  return new MyController;  
}  


