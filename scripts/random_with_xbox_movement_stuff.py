#!/usr/bin/env python

#Current Up To Date Usable Node
# Every python controller needs these lines
import roslib 
roslib.load_manifest('aj')
import rospy
from std_msgs.msg import UInt16
from sensor_msgs.msg import Joy
from time import sleep
import random
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

		self.axes = []
		self.buttons = []

		self.modes = {0:self.random_stuff, 1:self.spinny_stuff}
		self.current_mode = None
		self.random_stuffit = 0
		self.servo_1_angle = 0
		self.servo_2_angle = 0
		self.rate = 10
		self.current_iteration = 0
		#Subscribes to /basescan
		print "start Init"
		self.switch_1_sub = rospy.Subscriber("/limit_switch_1",UInt16,self.switch_1_callback)
		self.switch_2_sub = rospy.Subscriber("/limit_switch_2",UInt16,self.switch_2_callback)
		#self.base_scan_sub = rospy.Subscriber("/bool_array",UInt16,self.bool_array_callback)
		
		self.check_sub = rospy.Subscriber("/check",UInt16,self.check_callback)
		self.check_val_sub = rospy.Subscriber("/check_val",UInt16,self.check_val_callback)
		self.joy_sub = rospy.Subscriber("/joy",Joy,self.joy_callback)
		

		self.pwm_1_pub = rospy.Publisher('/pwm_1', UInt16)
		self.bool_pub = rospy.Publisher('/bool', UInt16)
		
		self.servo_1_pub = rospy.Publisher('/servo_1', UInt16)
		self.servo_2_pub = rospy.Publisher('/servo_2', UInt16)

		self.servo_1_pub.publish(90)
		self.servo_2_pub.publish(90)

		print "End Init"

	def joy_callback(self, joy_values):
		self.axes = joy_values.axes
		self.buttons = joy_values.buttons

		print self.axes[3]			
		print self.axes[4]			
		if (self.axes[0] > .4):
			self.bool_pub.publish(self.in_a_true)
			self.bool_pub.publish(self.in_b_false)
		if (self.axes[0] < -.4):
			self.bool_pub.publish(self.in_a_false)
			self.bool_pub.publish(self.in_b_true)	
		if (self.axes[0] < .4 and self.axes[0] > -.4):
			self.bool_pub.publish(self.in_a_false)
			self.bool_pub.publish(self.in_b_false)
		if  (self.axes[5] > 0):
			self.bool_pub.publish(self.en_false)
		if  (self.axes[5] < 0):
			self.bool_pub.publish(self.en_true)	


		if self.current_mode == None:
			self.current_mode = random.randint(0, 0)

		#Try to prevent the random movements going too fast and breaking something.
		if self.current_iteration >= self.rate:
			self.modes[self.current_mode]
			self.current_iteration = 0 

#		if (self.axes[3] is not None):
#			servo_1_angle = (((self.axes[3]*-1)+1)*90)
#			self.servo_1_pub.publish(servo_1_angle)
#		if (self.axes[4] is not None):
#			servo_2_angle = ((self.axes[4]+1)*90)
#			self.servo_2_pub.publish(servo_2_angle)	

	
	#servo 1 - 45 servo 2 - 90 add x to 45 and subtract x from 90 until 90-45
	#servo 1 - 90 servo 2 - 45 add x to 90 and add x to 45 until 135-90
	#servo 1 - 135 servo 2 - 90 subtract x to 135 and add x to 90 until 90-135
	#servo 1 - 90 servo 2 - 135 subtract x to 90 and subtract x from 135 until 45-90
	def spinny_stuff(self):
		if self.spinny_mode == None:
			self.spinny_stuff.spinny_mode = 0
			self.servo_1_pub.publish(45)
			self.servo_2_pub.publish(90)
			return

		if self.spinny_stuff.spinny_mode == 0:
			self.servo_1_angle += 5
			self.servo_2_angle -= 5

		if self.spinny_stuff.spinny_mode == 1:
			self.servo_1_angle += 5
			self.servo_2_angle += 5

		if self.spinny_stuff.spinny_mode == 2:
			self.servo_1_angle -= 5
			self.servo_2_angle += 5

		if self.spinny_stuff.spinny_mode == 3:
			self.servo_1_angle -= 5
			self.servo_2_angle -= 5



		if self.servo_1_angle == 90 and self.servo_2_angle == 45:
			self.spinny_stuff.spinny_mode += 1
		if self.servo_1_angle == 135 and self.servo_2_angle == 90:
			self.spinny_stuff.spinny_mode += 1
		if self.servo_1_angle == 90 and self.servo_2_angle == 135:
			self.spinny_stuff.spinny_mode += 1
		if self.servo_1_angle == 45 and self.servo_2_angle == 90:
			self.spinny_stuff.spinny_mode = None
			self.current_mode = None

		self.servo_1_pub.publish(self.servo_1_angle)
		self.servo_2_pub.publish(self.servo_2_angle)

	#Move in small random directions for some random iterations
	def random_stuff(self):
		self.random_stuffit += random.randint(1, 5)
		self.servo_1_angle += random.randint(-4, 4)
		self.servo_2_angle += random.randint(-4, 4)
		self.servo_1_pub.publish(self.servo_1_angle)
		self.servo_2_pub.publish(self.servo_2_angle)

		
		if self.random_stuffit < 20:
			self.current_mode = None
	#def square_stuff(self):

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
	rospy.init_node('random_with_xbox_movement_stuff',log_level=rospy.DEBUG)
	controller = controller()
	rospy.spin()
