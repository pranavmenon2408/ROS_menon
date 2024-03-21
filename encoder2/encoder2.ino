#include <Encoder.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#define ENCODER_A 17
#define ENCODER_B 18

#define ENCODER_C 17
#define ENCODER_D 18

std_msgs::Int16 odom1_msg;
std_msgs::Int16 odom2_msg;
ros::Publisher odom1("back_left_ticks",&odom1_msg);
ros::Publisher odom2("back_right_ticks",&odom2_msg);
ros::NodeHandle nh;
volatile long count1 = 0;
volatile long count2 = 0;

Encoder myEncoder1(ENCODER_A, ENCODER_B);
Encoder myEncoder2(ENCODER_C, ENCODER_D);

void encoderISR1() {
  if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
    count1++;
  } else {
    count1--;
  }  
}

void encoderISR2() {
  if (digitalRead(ENCODER_C) == digitalRead(ENCODER_D)) {
    count2++;
  } else {
    count2--;
  }  
}

void setup() {
  nh.initNode();
  nh.advertise(odom1);
  nh.advertise(odom2);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderISR1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_C), encoderISR2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_D), encoderISR2, CHANGE);
}

void loop() {
  long position1 = count1;
  long position2=count2; 
  Serial.println(position1);
  Serial.println(position2);
  odom1_msg.data=position1;
  odom2_msg.data=position2;
  odom1.publish(&odom1_msg);
  odom2.publish(&odom2_msg);
  nh.spinOnce();
    
  

 
 }
