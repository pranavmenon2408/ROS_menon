#!/usr/bin/env python
import rospy
from ros_package.msg import joystick
from std_msgs.msg import String

class Direction:
 def __init__(self):
    rospy.init_node('new_topic_sub',anonymous=True)
    self.pub=rospy.Publisher("/sample",String,queue_size=10)
   
    
    self.axis=joystick()
    
    self.rate=rospy.Rate(10)
 def callback(self,data):
    
    self.axis=data
    self.axis.x_axis=data.x_axis
    self.axis.y_axis=data.y_axis
    
    str_msg=String()
    str_msg.data="Executing"
   
    if self.axis.x_axis>125 and self.axis.x_axis<131:
       if self.axis.y_axis<120:
          str_msg.data="Forward"
       elif self.axis.y_axis>136:
          str_msg.data="Backward"
    elif self.axis.x_axis<120 :
       if self.axis.y_axis<120:
          str_msg.data="Forward Left"
       elif self.axis.y_axis>136:
          str_msg.data="Backward Left"
    elif self.axis.y_axis>125 and self.axis.y_axis<131:
       if self.axis.x_axis<120:
          str_msg.data="Left"
       elif self.axis.x_axis>136:
          str_msg.data="Right"
    elif self.axis.x_axis>136:
       if self.axis.y_axis<120:
          str_msg.data="Forward Right"
       elif self.axis.y_axis>136:
          str_msg.data="Backward Right"
    else:
       str_msg.data="Not moving"
    rospy.loginfo(str_msg) 
    self.pub.publish(str_msg)
    #print(axis_send.x_axis)
    #rospy.loginfo(axis_send)
    #self.pub.publish(axis_send)
 def listener(self):
    sub=rospy.Subscriber("/new_topic",joystick,self.callback)
    rospy.spin()
    

    
 
    
  

  
 
    
    
    
    
if __name__=="__main__":
    try:
       x=Direction()
       x.listener()
       
    except rospy.ROSInterruptException:
       pass
    
    
