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

        self.pub = rospy.Publisher('joystick/controller', joystick, queue_size=10)

        self.rate = rospy.Rate(10)

    def joyInit(self):

        pygame.init()

        pygame.joystick.init()

        # joystick_count = pygame.joystick.get_count()


    def getJoyInput(self):
        
        try:
            self.joystick_count = pygame.joystick.get_count()

            self.joystick = pygame.joystick.Joystick(0)

        except pygame.error:

            return -1
            
        self.joystick.init()

        event = pygame.event.get()

        if event:

            self.right_axisX = round(self.joystick.get_axis(2),2)
            self.right_axisY =  round(-self.joystick.get_axis(3),2)

            self.left_axisX =  round(self.joystick.get_axis(0),2)
            self.left_axisY =  round(-self.joystick.get_axis(1),2)

            if (abs(self.right_axisX) <= 0.2):
                self.right_axisX = 0.0

            if (abs(self.right_axisY) <= 0.2):
                self.right_axisY = 0.0

            if (abs(self.left_axisX) <= 0.2):
                self.left_axisX = 0.0

            if (abs(self.left_axisY) <= 0.2):
                self.left_axisY = 0.0


            button_up = self.joystick.get_button(2)

            button_down = self.joystick.get_button(0)

            # print("button_up : {}".format(button_up))
            # print("button_down : {}".format(button_down))
            # print(type(button_up))
            # print((button_up == 1))
            # print((button_up == 0))
            # print((button_up == 0))

            if button_up == 1:
                self.button_axisZ = 1

            elif button_down == 1:
                self.button_axisZ = -1

            else:
                self.button_axisZ =0


            print("button_axisZ: {}".format(self.button_axisZ))


        
            return True

        else:

            return False


    def filterJoyInput(self):

        pass

    def pushJoyOutput(self):

        joy_msg = joystick()

        joy_msg.rh_axisX = self.right_axisX
        joy_msg.rh_axisY = self.right_axisY

        joy_msg.lh_axisX = self.left_axisX
        joy_msg.lh_axisY = self.left_axisY

        joy_msg.button_axisZ = self.button_axisZ
        

        self.pub.publish(joy_msg)

        
def main():

    node =JoyNode()

    while not rospy.is_shutdown():

        res = node.getJoyInput()

        if res == -1:

            print("not found joystick")

        elif res == True:

            node.pushJoyOutput()

        else:

            print("no joystick input")

        node.rate.sleep()


if __name__ == '__main__':

    main()

