#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import atan2
PI=3.1415926535897
class TurtleBot:
 def __init__(self):
     rospy.init_node('makeaD',anonymous=True)
     self.pub=rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)
     self.sub=rospy.Subscriber('/turtle1/pose',Pose,self.callback)
     self.pose=Pose()
     self.rate=rospy.Rate(10)
 def callback(self,data):
     self.pose=data
     self.pose.x=round(self.pose.x,4)
     self.pose.y=round(self.pose.y,4)
     self.pose.theta=round(self.pose.theta,4)
    
 def makingD(self):
     
     radius=int(input("Enter radius"))
     vel_msg=Twist()
     rospy.loginfo(self.pose.x)
     vel_msg.linear.y=0
     vel_msg.linear.z=0
     vel_msg.angular.x=0
     vel_msg.angular.y=0
     vel_msg.linear.x=0
     vel_msg.angular.z=0
     self.pub.publish(vel_msg)
     self.rate.sleep()
     rospy.loginfo(self.pose.y)
     x=self.pose.x
     y=self.pose.y
     
     
    
     vel_msg.linear.x=radius
     vel_msg.angular.z=1
     while(self.pose.y<(y+2*radius)-0.003):
         self.pub.publish(vel_msg)
         
         self.rate.sleep()
     vel_msg.linear.x=0
     vel_msg.angular.z=0
     self.pub.publish(vel_msg)
     self.rate.sleep()
     rospy.loginfo(self.pose.y) 
     theta=abs(round(atan2(y-self.pose.y,x-self.pose.x),4))
     
     rospy.loginfo(theta)
     
     t0=rospy.Time.now().to_sec()
     current_angle=0
     vel_msg.angular.z=0.5
     
     while(current_angle<theta):
         self.pub.publish(vel_msg)
         t1=rospy.Time.now().to_sec()
         current_angle=((t1-t0)*0.5)
         self.rate.sleep()
     vel_msg.angular.z=0
     self.pub.publish(vel_msg)
     
     current_dist=0
     vel_msg.linear.x=1
     t2=rospy.Time.now().to_sec()
     while(current_dist<(2*radius)):
           self.pub.publish(vel_msg)
           t3=rospy.Time.now().to_sec()
           current_dist=1*(t3-t2)
           self.rate.sleep()
     vel_msg.linear.x=0
     self.pub.publish(vel_msg)
     """current_angle1=0
     vel_msg.angular.z=-(10*PI/180)
     t4=rospy.Time.now().to_sec()
     while(current_angle1<PI/2):
         self.pub.publish(vel_msg)
         t5=rospy.Time.now().to_sec()
         current_angle1=10*PI*(t5-t4)/180
         self.rate.sleep()
     vel_msg.angular.z=0
     self.pub.publish(vel_msg) 
     vel_msg.linear.x=2
     vel_msg.angular.z=-2"""

     
     #while(self.pose.x>5.20000 && self.pose.x<5.50000):
         #self.pub.publish(vel_msg)
         #self.rate.sleep()
     #vel_msg.linear.x=0
     #vel_msg.angular.z=0
     #self.pub.publish(vel_msg)
     rospy.spin()
if __name__ == '__main__':
   try:
      x=TurtleBot()
      x.makingD()
   except rospy.ROSInterruptException:
      pass                     
     
