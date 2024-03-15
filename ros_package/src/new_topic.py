import rospy
import random
from ros_package.msg import joystick

def publish():
    pub=rospy.Publisher('/new_topic',joystick,queue_size=10)
    rospy.init_node('new_topic')
    rate=rospy.Rate(10)
    while not rospy.is_shutdown():
       axis=joystick()
       x=random.randint(0,255)
       y=random.randint(0,255)
       axis.x_axis=x
       axis.y_axis=y
       rospy.loginfo(axis)
       pub.publish(axis)
       rate.sleep()
       
if __name__=="__main__":
    try:
       publish()
    except rospy.ROSInterruptException:
       pass
       
