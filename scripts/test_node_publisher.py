import rospy
import roslib
from std_msgs.msg import UInt16

self.check_value = 1

def talker():
    self.check_pub = rospy.Publisher('/check', UInt16)
    rospy.init_node('talker', anonymous=True)
    r = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        
        self.check_pub.publish(self.check_value)
        r.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass