#!/usr/bin/env python


# Every python controller needs these lines
import roslib 
roslib.load_manifest('aj')
import rospy
from std_msgs.msg import UInt16
from time import sleep
# The velocity command message

class controller:
	def __init__(self):
		#Subscribes to /basescan
		print "start Init"
		self.base_scan_sub = rospy.Subscriber("/limit_switch_1",UInt16,self.switch_1_callback)
		self.base_scan_sub = rospy.Subscriber("/limit_switch_2",UInt16,self.switch_2_callback)
		self.base_scan_sub = rospy.Subscriber("/check",UInt16,self.check_callback)
		self.base_scan_sub = rospy.Subscriber("/check_val",UInt16,self.check_val_callback)
		

		self.pwm_1_pub = rospy.Publisher('/pwm_1', UInt16)
		self.led_pub = rospy.Publisher('/led', UInt16)
		self.in_a_pub = rospy.Publisher('/in_a', UInt16)
		self.in_b_pub = rospy.Publisher('/in_b', UInt16)
		self.motor_enable_pub = rospy.Publisher('/motor_enable', UInt16)

		self.led_bool = 0

		print "End Init"

	def switch_1_callback(self, switch_bool):
		self.in_a_pub.publish
		()
		self.in_b_pub.publish()
		print "Switch 1 Callback"
	
	def switch_2_callback(self, switch_bool):
		self.in_a_pub.publish()
		self.in_b_pub.publish()
		print "Switch 2 Callback"
	
	def check_callback(self, check):
		
		print "check callback"
		
	def check_val_callback(self, check_val):
		print check_val

if __name__ == '__main__':
	rospy.init_node('aj',log_level=rospy.DEBUG)
	controller = controller()
	rospy.spin()
