#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
PI=3.1415926535897
def hexagon():
   
   rospy.init_node('hexagon',anonymous=True)
   vel_pub=rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)
   vel_msg=Twist()
   
   side=int(input("Enter length of hexagon side: "))
   
   vel_msg.linear.y=0
   vel_msg.linear.z=0
   vel_msg.angular.x=0
   vel_msg.angular.y=0
   vel_msg.angular.z=0
   theta=60*PI/180
   angspeed=30*PI/180
   for i in range(0,6):
       current=0
       
       vel_msg.linear.x=1
       t1=rospy.Time.now().to_sec()
       while(current<side):
          vel_pub.publish(vel_msg)
          t2=rospy.Time.now().to_sec()
          current=1*(t2-t1)
       vel_msg.linear.x=0
       vel_pub.publish(vel_msg)
       vel_msg.angular.z=angspeed
       current2=0
       t3=rospy.Time.now().to_sec()
       while(current2<theta):
          vel_pub.publish(vel_msg)
          t4=rospy.Time.now().to_sec()
          current2=angspeed*(t4-t3)  
       vel_msg.angular.z=0
       vel_pub.publish(vel_msg)    
          
          
       
    
       
if __name__ == '__main__':
   try:
      hexagon()
   except rospy.ROSInterruptException:
      pass   
