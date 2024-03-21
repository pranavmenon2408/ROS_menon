#include <ros.h>
#include <std_msgs/Int16.h>
ros::NodeHandle nh;
std_msgs::Int16 tick_msg1;
std_msgs::Int16 tick_msg2;
ros::Publisher tick1("/left_ticks",&tick_msg1);
ros::Publisher tick2("/right_ticks",&tick_msg2);
int encoderPin1 = 26;
int encoderPin2 = 27;

int encoderPin3 = 22;
int encoderPin4 = 23;

volatile int lastEncoded1 = 0;
volatile long encoderValue1 = 0;

volatile int lastEncoded2 = 0;
volatile long encoderValue2 = 0;

long lastencoderValue1 = 0;
long lastencoderValue2 = 0;
unsigned long pubPeriod = 50;
unsigned long previousTime;
int lastMSB1 = 0;
int lastLSB1 = 0;

int lastMSB2 = 0;
int lastLSB2 = 0;

void setup() {
  nh.initNode();
  nh.advertise(tick1);
  nh.advertise(tick2);
  pinMode(4, INPUT);
  Serial.begin(115200);

  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);

  pinMode(encoderPin3, INPUT_PULLUP);
  pinMode(encoderPin4, INPUT_PULLUP);

  attachInterrupt(encoderPin1, updateEncoder1, CHANGE);
  attachInterrupt(encoderPin2, updateEncoder1, CHANGE);

  attachInterrupt(encoderPin3, updateEncoder2, CHANGE);
  attachInterrupt(encoderPin4, updateEncoder2, CHANGE);
  previousTime = 0;
}

void loop() {
  //Serial.print("Angle =");
  if (previousTime + pubPeriod <= millis()){
  tick_msg1.data=encoderValue1-lastencoderValue1;
  tick_msg2.data=encoderValue2-lastencoderValue2;
  previousTime=millis();
  tick1.publish(&tick_msg1);
  tick2.publish(&tick_msg2);
  lastencoderValue1=encoderValue1;
  lastencoderValue2=encoderValue2;
  
  }
  //Serial.println(encoderValue1);
  Serial.println(encoderValue2);
  nh.spinOnce();
  
}


void updateEncoder1() {
  int MSB1 = digitalRead(encoderPin1);  //MSB = most significant bit
  int LSB1 = digitalRead(encoderPin2);  //LSB = least significant bit

  int encoded = (MSB1 << 1) | LSB1;          //converting the 2 pin value to single number
  int sum = (lastEncoded1 << 2) | encoded;  //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue1++; //13, 4, 2, 11
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue1--; //14, 7, 1, 8

  lastEncoded1 = encoded;  //store this value for next time
}
void updateEncoder2() {
  int MSB2 = digitalRead(encoderPin3);  //MSB = most significant bit
  int LSB2 = digitalRead(encoderPin4);  //LSB = least significant bit

  int encoded = (MSB2 << 1) | LSB2;          //converting the 2 pin value to single number
  int sum = (lastEncoded2 << 2) | encoded;  //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue2++; //13, 4, 2, 11
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue2--; //14, 7, 1, 8

  lastEncoded2 = encoded;  //store this value for next time
}
