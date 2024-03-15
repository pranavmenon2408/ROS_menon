#!/usr/bin/env python3
import rospy, math, time
from geometry_msgs.msg import Twist, Pose2D

def Talker():
    pub=rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    rospy.init_node('rotator', anonymous=True)
    rate = rospy.Rate(10)
    msg = Twist()
    while not rospy.is_shutdown():
        msg.linear.x = 3
        msg.linear.y=0
        msg.linear.z=0
        msg.angular.x=0
        msg.angular.y=0
        msg.angular.z=3
        pub.publish(msg)
        rate.sleep()
    
if __name__=='__main__':
    try:
        Talker()
    except rospy.ROSInterruptException:
        pass