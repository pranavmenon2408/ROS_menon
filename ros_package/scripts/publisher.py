#!/usr/bin/env python3
import rospy
from ros_package.msg import nazi

def talk_to_me():
     pub =rospy.Publisher('chatter', nazi, queue_size=10)
     rospy.init_node('publisher',anonymous=True)
     rate =rospy.Rate(10)
     while not rospy.is_shutdown():
          msg =nazi()
          msg.front=30
          msg.right=255
          msg.left=-240
          msg.back=10
          rospy.loginfo(msg)
          pub.publish(msg)
          rate.sleep()
if __name__ == '__main__':
   try:
      talk_to_me()
   except rospy.ROSInterruptException:
      pass     
      
