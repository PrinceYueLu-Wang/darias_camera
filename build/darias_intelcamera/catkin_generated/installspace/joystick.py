#!/usr/bin/env python3

import pygame
import rospy
from std_msgs.msg import Float32,String

from darias_intelcamera.msg import joystick


class JoyNode():


    def __init__(self):

        self.rosInit()

        self.joyInit()

        self.right_axisX = 0.0
        self.right_axisY = 0.0

    def rosInit(self):

        rospy.init_node('joystick_node', anonymous=False)
        
        # self.pub_button = rospy.Publisher('joystick/button', String, queue_size=10)

        # self.pub_axis = rospy.Publisher('joystick/axis', String, queue_size=10)

        self.pub = rospy.Publisher('joystick/controller', joystick, queue_size=10)

        self.rate = rospy.Rate(10)

    def joyInit(self):

        pygame.init()

        pygame.joystick.init()

        joystick_count = pygame.joystick.get_count()

        # if joystick_count == 0:

        #     return False

        # else:
        #     return True


    def getJoyInput(self):

        self.joystick_count = pygame.joystick.get_count()
        self.joystick = pygame.joystick.Joystick(0)
        self.joystick.init()

        event = pygame.event.get()

        if event:

            # buttons = self.joystick.get_numbuttons()

            # print("Number of buttons: {}".format(buttons))

            # for i in range(buttons):
            #     button = self.joystick.get_button(i)
            #     if button == 1:
            #         self.detect_input = True

            #         print("Button {} value: {}".format(i, button))
            #         self.button_name=i
            #         self.button_value = button

            self.right_axisX = self.joystick.get_axis(2)
            self.right_axisY = -self.joystick.get_axis(3)

        
            return True

        else:

            return False


    def filterJoyInput(self):

        pass

    def pushJoyOutput(self):

        joy_msg = joystick()

        joy_msg.rh_axisX = self.right_axisX
        joy_msg.rh_axisY = self.right_axisY

        self.pub.publish(joy_msg)

        
def main():

    node =JoyNode()

    while not rospy.is_shutdown():

        res = node.getJoyInput()

        if res :

            node.pushJoyOutput()

        else:

            print("no joystick input")

        node.rate.sleep()


if __name__ == '__main__':

    main()

