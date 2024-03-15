#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
import socket

# addres="94:E6:86:3C:EC:6E"
# channel = 1
# s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, 
# socket.BTPROTO_RFCOMM)



def cmd_vel_callback(msg):
    # Convert linear and angular velocities to holonomic drive commands
    vx = msg.linear.x*2
    #vy = msg.linear.y*2
    wz = msg.angular.z*1.1

    # Calculate the individual wheel speeds for a holonomic drive
    left_front_wheel = (vx - wz)*100
    right_front_wheel= (vx + wz)*100
    left_rear_wheel = (vx - wz)*100
    right_rear_wheel = (vx + wz)*100
    print(left_front_wheel,right_front_wheel,left_rear_wheel,right_rear_wheel)

    # Send the wheel speeds to the ESP32 via Bluetooth
    cmd = f"Z{left_front_wheel},{right_front_wheel},{left_rear_wheel},{right_rear_wheel}\n"
    #s.send(cmd.encode())

def main():

    #s.connect((addres,channel))
    print("ready")
    rospy.init_node('blue_control')
    rospy.Subscriber('/cmd_vel', Twist, cmd_vel_callback)
    rospy.spin()

if __name__ == '__main__':
    main()
