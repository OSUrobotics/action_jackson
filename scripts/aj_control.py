#!/usr/bin/env python

#Current Up To Date Usable Node
# Every python controller needs these lines
import roslib 
roslib.load_manifest('aj')
import rospy
from std_msgs.msg import UInt16
from time import sleep
# The velocity command message

class controller:
	def __init__(self):
		self.led_bool = 0
		self.en_bool = 0
		self.in_a_bool = 0
		self.in_b_bool = 0

		self.led_true = 1
		self.led_false = 2
		self.en_true = 3
		self.en_false = 4
		self.in_a_true = 5
		self.in_a_false = 6
		self.in_b_true = 7
		self.in_b_false = 8

		#Subscribes to /basescan
		print "start Init"
		self.base_scan_sub = rospy.Subscriber("/limit_switch_1",UInt16,self.switch_1_callback)
		self.base_scan_sub = rospy.Subscriber("/limit_switch_2",UInt16,self.switch_2_callback)
		#self.base_scan_sub = rospy.Subscriber("/bool_array",UInt16,self.bool_array_callback)
		
		self.base_scan_sub = rospy.Subscriber("/check",UInt16,self.check_callback)
		self.base_scan_sub = rospy.Subscriber("/check_val",UInt16,self.check_val_callback)
		

		self.pwm_1_pub = rospy.Publisher('/pwm_1', UInt16)
		self.bool_pub = rospy.Publisher('/bool', UInt16)
		
		print "End Init"

	def switch_1_callback(self, switch_bool):
		self.bool_pub.publish(self.in_a_false)
		self.bool_pub.publish(self.in_b_true)
		print "Switch 1 Callback"
	
	def switch_2_callback(self, switch_bool):
		self.bool_pub.publish(self.in_a_true)
		self.bool_pub.publish(self.in_b_false)
		print "Switch 2 Callback"
	
#	def bool_array_callback(self, bool_array):


	def check_callback(self, check):
		self.bool_pub.publish
		print "check callback"
		
	def check_val_callback(self, check_val):
		print check_val

if __name__ == '__main__':
	rospy.init_node('aj',log_level=rospy.DEBUG)
	controller = controller()
	rospy.spin()
