/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * Angles are given in degrees
 * Note that X and Y are tilt angles and not pitch/roll.
 *
 * License: MIT
 */
#include <ros.h>
#include "Wire.h"
#include <MPU6050_light.h>
#include <sensor_msgs/Imu.h>
#include <math.h>
ros::NodeHandle nh;
sensor_msgs::Imu imu_msg;
ros::Publisher imu("imu",&imu_msg);

MPU6050 mpu(Wire);

long timer = 0;
float rollRad,pitchRad,yawRad;

void setup() {
  nh.initNode();
  nh.advertise(imu);
  Serial.begin(19200);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  
}

void loop() {
  mpu.update();

  if(millis() - timer > 0){ // print data every second
    Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
    Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX());
    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
  
    Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.println(F("=====================================================\n"));
    imu_msg.linear_acceleration.x = mpu.getAccX();
    imu_msg.linear_acceleration.y = mpu.getAccY();
    imu_msg.linear_acceleration.z = mpu.getAccZ();
    
//    // Set covariance matrix for linear acceleration
    imu_msg.linear_acceleration_covariance[0] = 0.01;
    imu_msg.linear_acceleration_covariance[4] = 0.01;
    imu_msg.linear_acceleration_covariance[8] = 0.01;
    
    imu_msg.angular_velocity.x = mpu.getGyroX();
    imu_msg.angular_velocity.y = mpu.getGyroY();
    imu_msg.angular_velocity.z = mpu.getGyroZ();
    
//    // Set covariance matrix for angular velocity
    imu_msg.angular_velocity_covariance[0] = 0.01;
    imu_msg.angular_velocity_covariance[4] = 0.01;
    imu_msg.angular_velocity_covariance[8] = 0.01;

    rollRad = mpu.getAngleX() * M_PI / 180.0;
    pitchRad = mpu.getAngleY() * M_PI / 180.0;
    yawRad = mpu.getAngleZ() * M_PI / 180.0;
    
    // Calculate quaternion components
    imu_msg.orientation.x = sin(rollRad / 2) * cos(pitchRad / 2) * cos(yawRad / 2) - cos(rollRad / 2) * sin(pitchRad / 2) * sin(yawRad / 2);
    imu_msg.orientation.y = cos(rollRad / 2) * sin(pitchRad / 2) * cos(yawRad / 2) + sin(rollRad / 2) * cos(pitchRad / 2) * sin(yawRad / 2);
    imu_msg.orientation.z = cos(rollRad / 2) * cos(pitchRad / 2) * sin(yawRad / 2) - sin(rollRad / 2) * sin(pitchRad / 2) * cos(yawRad / 2);
    imu_msg.orientation.w = cos(rollRad / 2) * cos(pitchRad / 2) * cos(yawRad / 2) + sin(rollRad / 2) * sin(pitchRad / 2) * sin(yawRad / 2);
    

    imu_msg.orientation_covariance[0] = 0.01; // Covariance for roll
    imu_msg.orientation_covariance[4] = 0.01; // Covariance for pitch
    imu_msg.orientation_covariance[8] = 0.01;
    imu.publish(&imu_msg);
    timer = millis();
    nh.spinOnce();
    
  }

}
