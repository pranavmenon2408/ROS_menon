#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import pow, atan2, sqrt

class TurtleBot:
    def __init__(self):
        rospy.init_node('go2goal',anonymous=True)
        self.pub=rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)
        self.sub=rospy.Subscriber('/turtle1/pose',Pose,self.update_pose)
        self.pose=Pose()
        self.rate=rospy.Rate(10)
        
    def update_pose(self,data):
       self.pose=data
       self.pose.x=round(self.pose.x,4)
       self.pose.y=round(self.pose.y,4)
       
    def euclidean_distance(self,goal_pose):
       return sqrt(pow((goal_pose.x-self.pose.x),2)+pow((goal_pose.y-self.pose.y),2))
       
    def linear_vel(self,goal_pose):
       return 0.5*self.euclidean_distance(goal_pose)
       
    def steering_angle(self,goal_pose):
       return atan2((goal_pose.y-self.pose.y),(goal_pose.x-self.pose.x))
       
    def angular_vel(self,goal_pose):
       return 2.0*(self.steering_angle(goal_pose)-self.pose.theta)   
       
    def move2goal(self):
       vel_msg=Twist()
       goal_pose=Pose()
       goal_pose.x=float(input("Enter x coordinate of goal:"))
       goal_pose.y=float(input("Enter y coordinate of goal:"))
       
       while self.euclidean_distance(goal_pose) >=0.001:
          vel_msg.linear.x=self.linear_vel(goal_pose)
          vel_msg.linear.y=0
          vel_msg.linear.z=0
          vel_msg.angular.x=0
          vel_msg.angular.y=0
          vel_msg.angular.z=self.angular_vel(goal_pose)
          self.pub.publish(vel_msg)
          self.rate.sleep()
          
       vel_msg.linear.x=0
       vel_msg.angular.z=0   
       self.pub.publish(vel_msg)
       rospy.loginfo("X-coordinate: %f",round(self.pose.x,1))
       rospy.loginfo("Y-coordinate %f",round(self.pose.y,1))
       rospy.spin()
       
if __name__ =='__main__':
  try:
     x=TurtleBot()
     x.move2goal()
  except rospy.ROSInterruptException:
     pass                        
