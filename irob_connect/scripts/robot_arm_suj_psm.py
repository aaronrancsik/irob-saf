#!/usr/bin/env python
import sys
import time

import roslibpy
import rospy
from twisted.internet import reactor

from sensor_msgs.msg import JointState

from rospy_message_converter import message_converter

from robot_arm_dvrk import RobotArmDVRK


class RobotArmSUJPSM(RobotArmDVRK):

  def __init__(self, name, namespace, ros):
    RobotArmDVRK.__init__(self, name, namespace, ros,
            {'J0': 'J0',
            'J1': 'J1',
            'J2': 'J2',
            'J3': 'J3',
            'J4': 'J4'},

            ['J0','J1','J2','J3','J4'])

  def subscribe_to_topics(self):
    print('Dummy ' + self.name + ', not subscribing.')






































