#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

def move():
   rospy.init_node('linmotion',anonymous=True)
   vel_pub= rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)
   vel_msg=Twist()
   print("To move the turtle")
   speed=int(input("Enter speed: "))
   dist=int(input("Enter distance: "))
   isForward=int(input("Forward? (1 for Yes,0 for no)"))
   
   if(isForward):
      vel_msg.linear.x=abs(speed)
   else:
      vel_msg.linear.x= -abs(speed)
   
   vel_msg.linear.y=0
   vel_msg.linear.z=0
   vel_msg.angular.x=0
   vel_msg.angular.y=0
   vel_msg.angular.z=0
   
   while not rospy.is_shutdown():
        
        t1=rospy.Time.now().to_sec()
        current_dist=0
        
        while(current_dist<dist):
           vel_pub.publish(vel_msg)
           t2=rospy.Time.now().to_sec()
           current_dist=speed*(t2-t1)
        vel_msg.linear.x=0
        vel_pub.publish(vel_msg)
        
if __name__ == '__main__':
   try:
       move()
   except rospy.ROSInterruptException:
       pass    
