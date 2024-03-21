
#include <ros.h>


#include <ros_package/nazi.h>
#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>

Cytron_PS2Shield ps2(2, 3); 
ros::NodeHandle nh;

ros_package::nazi vel;
ros::Publisher chatter("/wheelvel", &vel);
int rawvalx,rawvaly;
int wheelvels[4];

void nazi(int x,int y,int output[]){
  float z = sqrt(x * x + y * y);
  float rad = atan2(y,x);
  float angle = rad * 180 /PI;
  //Serial.print("angle:");Serial.println(angle);

    if(angle>90)
    {
      angle = 450 - angle;
    }
    else
    {
      angle = 90 - angle;
    }

    angle = (angle*PI)/180.0; //degrees to radians
    //0,90,180,270
    float wheel_angles[4]={0, (90 * PI) /180.0, (180 * PI) /180.0,(270 * PI) /180.0};


    for(int i=0; i < 4;i++){
         float wv = z*sin(angle)*sin(wheel_angles[i])+z*cos(angle)*cos(wheel_angles[i]);
         output[i] = int(wv);
    }
    output[1]=-output[1];
    output[2]=-output[2];
}
/*void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");    
}

const int freq = 5000;
const int resolution = 8;
void notify(){
  if (millis() - lastTimeStamp > 20)
  {
    rawvalx=PS4.LStickX()*2;
    rawvaly=PS4.LStickY()*2;


  


  //Only needed to print the message properly on serial monitor. Else we dont need it.

    nazi(rawvalx,rawvaly,wheelvels);
    vel.right=wheelvels[0];
    vel.front=wheelvels[1];
    vel.left=wheelvels[2];
    vel.back=wheelvels[3];
    
  
    chatter.publish( &vel );
    lastTimeStamp = millis();
    nh.spinOnce();
    
    
  }
  nh.spinOnce();
  
  
}*/

void setup() {
  // put your setup code here, to run once:
  ps2.begin(57600);
  Serial.begin(57600);
  nh.initNode();
  
  nh.advertise(chatter);
  
  
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
   rawvalx=ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS);
   rawvaly=ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS);
   Serial.println(rawvalx+" "+rawvaly);
   nazi(rawvalx,rawvaly,wheelvels);
   vel.right=wheelvels[0];
   vel.front=wheelvels[1];
   vel.left=wheelvels[2];
   vel.back=wheelvels[3];
    
  
   chatter.publish( &vel );
    
   nh.spinOnce();
   
  
  
  
  

}
