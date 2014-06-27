#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import UInt16

def talker():
    check = 1
    pub = rospy.Publisher('/check', UInt16, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    r = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        pub.publish(check)
        r.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass