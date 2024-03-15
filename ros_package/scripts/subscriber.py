#!/usr/bin/env python
import rospy
from ros_package.msg import custom
def callback(data):
   rospy.loginfo("I heard %s %f %d ",data.message, data.dec,data.num)
def listener():
   rospy.init_node("subscriber", anonymous=True)
   rospy.Subscriber('chatter',custom,callback)
   rospy.spin()
if __name__ == '__main__':
   try:
     listener()
   except rospy.ROSInterruptException:
     pass        
