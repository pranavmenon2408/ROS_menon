#!/usr/bin/env python
import rospy 
from sensor_msgs.msg import Range
from std_msgs.msg import Int32



def callback(data):
    
    pub=rospy.Publisher("/wall_front",Int32,queue_size=10)
    if data.range<0.75 and data.range>0.001:
       pub.publish(1)
    else:
       pub.publish(0)
       
def callback2(data):
    
    pub=rospy.Publisher("/wall_left",Int32,queue_size=10)
    if data.range<0.75 and data.range>0.001:
       pub.publish(1)
    else:
       pub.publish(0)
       
def callback3(data):
    
    pub=rospy.Publisher("/wall_right",Int32,queue_size=10)
    if data.range<0.75 and data.range>0.001:
       pub.publish(1)
    else:
       pub.publish(0)
    
def listener():
    
    rospy.init_node("Range_sub",anonymous=True)
    rospy.Subscriber("/sensor_msgs/Range",Range,callback)
    rospy.Subscriber("/sensor_msgs/Range2",Range,callback2)
    rospy.Subscriber("/sensor_msgs/Range3",Range,callback3)
    rospy.spin()
    
if __name__ == "__main__":
    
    try:
        listener()
    except rospy.ROSInterruptException:
        pass
  
