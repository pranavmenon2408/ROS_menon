int dirPin1 = 25,  dirPin2 = 32, dirPin3 = 12, dirPin4 = 18;
int pwmPin1 = 33,  pwmPin2 = 35, pwmPin3 = 14,  pwmPin4 = 19;

int speed = 20, frequency = 500,wheel1,wheel2,wheel3,wheel4; 
#include <ros.h>
#include <std_msgs/Int16.h>


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

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

BluetoothSerial SerialBT;
String data = "";

void WheelCommands(int raw_val,int dir_pin,int pwm_pin){
  if(raw_val>0){
    digitalWrite(dir_pin,1);
    analogWrite(pwm_pin,raw_val);
  }
  else{
    digitalWrite(dir_pin,0);
    analogWrite(pwm_pin,-raw_val);
    
  }


  
}

void forward(){
  Serial.println("Forward");

  digitalWrite(dirPin1, 1);
  analogWrite(pwmPin1, speed);

  digitalWrite(dirPin2, LOW);
  analogWrite(pwmPin2, 0);

  digitalWrite(dirPin3, 1);
  analogWrite(pwmPin3, speed);

  digitalWrite(dirPin4, LOW);
  analogWrite(pwmPin4, 0);
}


void backward(){
  Serial.println("Backward");

  digitalWrite(dirPin1, 0);
  analogWrite(pwmPin1, speed);

  digitalWrite(dirPin2, LOW);
  analogWrite(pwmPin2, 0);

  digitalWrite(dirPin3, 0);
  analogWrite(pwmPin3, speed);

  digitalWrite(dirPin4, LOW);
  analogWrite(pwmPin4, 0);
}


void left(){
  Serial.println("Left");

  digitalWrite(dirPin1, 1);
  analogWrite(pwmPin1, 0);

  digitalWrite(dirPin2, 1);
  analogWrite(pwmPin2, speed);

  digitalWrite(dirPin3, LOW);
  analogWrite(pwmPin3, 0);

  digitalWrite(dirPin4, LOW);
  analogWrite(pwmPin4, speed);

  
}


void right(){
  Serial.println("Right");

  digitalWrite(dirPin1, 0);
  analogWrite(pwmPin1, 0);

  digitalWrite(dirPin2, 0);
  analogWrite(pwmPin2, speed);

  digitalWrite(dirPin3, LOW);
  analogWrite(pwmPin3, 0);

  digitalWrite(dirPin4, HIGH);
  analogWrite(pwmPin4, speed);
}


void clockwise(){
  Serial.println("Clockwise");

  digitalWrite(dirPin1, HIGH);
  analogWrite(pwmPin1, speed);

  digitalWrite(dirPin2, 0);
  analogWrite(pwmPin2, speed);

  digitalWrite(dirPin3, LOW);
  analogWrite(pwmPin3, speed);

  digitalWrite(dirPin4, LOW);
  analogWrite(pwmPin4, speed);
}


void anticlockwise(){
  Serial.println("Anticlockwise");

  digitalWrite(dirPin1, LOW);
  analogWrite(pwmPin1, speed);

  digitalWrite(dirPin2, 1);
  analogWrite(pwmPin2, speed);

  digitalWrite(dirPin3, HIGH);
  analogWrite(pwmPin3, speed);

  digitalWrite(dirPin4, HIGH);
  analogWrite(pwmPin4, speed);
}

void stop(){
  Serial.println("Stop");

  digitalWrite(dirPin1, LOW);
  analogWrite(pwmPin1, 0);

  digitalWrite(dirPin2, LOW);
  analogWrite(pwmPin2, 0);

  digitalWrite(dirPin3, LOW);
  analogWrite(pwmPin3, 0);

  digitalWrite(dirPin4, LOW);
  analogWrite(pwmPin4, 0);
}

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
  pinMode(pwmPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(pwmPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);

  pinMode(13, OUTPUT);

  
  SerialBT.begin("NaziDrive"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {

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
  //Serial.println(encoderValue2);
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar=='Z'){
      data = SerialBT.readStringUntil(',');  
      wheel1=data.toInt(); 
      data = SerialBT.readStringUntil(',');  
      wheel2=data.toInt();
      data = SerialBT.readStringUntil(',');  
      wheel3=data.toInt();
      data = SerialBT.readStringUntil('\n');
      wheel4=data.toInt();

      WheelCommands(wheel1,dirPin1,pwmPin1);
      WheelCommands(-wheel2,dirPin2,pwmPin2);
      WheelCommands(wheel3,dirPin3,pwmPin3);
      WheelCommands(wheel4,dirPin4,pwmPin4);
      Serial.print(wheel1);
      Serial.print(",");
      Serial.print(wheel2);
      Serial.print(",");
      Serial.print(wheel3);
      Serial.print(",");
      Serial.println(wheel4);
    }
    else{
    if ((incomingChar >= '1' && incomingChar <= '9') || 'q' == incomingChar) {
        if ('Q' == incomingChar) {
            speed=(100);
        } else {
            speed=((incomingChar - '0') * 10);
        }
    }
    if (incomingChar == 'F'){
      forward();
    }
    else if (incomingChar == 'B'){
      backward();
    }
    else if (incomingChar == 'L'){
      left();
    }
    else if (incomingChar == 'R'){
      right();
    }
    else if (incomingChar == 'G'){
      anticlockwise();
    }
    else if (incomingChar == 'I'){
      clockwise();
    }
    else{
       stop();
    }
    Serial.println(speed);
    }
  }
  nh.spinOnce();
}
  
  //delay(10);}
  
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

 
