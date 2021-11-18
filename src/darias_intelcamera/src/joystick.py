import pygame
import rospy
from std_msgs.msg import Float32,String

class JoyNode():


    def __init__(self):

        self.rosInit()

        self.joyInit()

    def rosInit(self):

        rospy.init_node('talker', anonymous=True)
        
        self.pub = rospy.Publisher('chatter', String, queue_size=10)
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

            buttons = self.joystick.get_numbuttons()
            # print("Number of buttons: {}".format(buttons))

            for i in range(buttons):
                button = self.joystick.get_button(i)
                if button == 1:
                    self.detect_input = True

                    print("Button {} value: {}".format(i, button))
                    self.button_name=i
                    self.button_value = button

            return True

        else:

            return False


    def filterJoyInput(self):

        pass

    def pushJoyOutput(self):

        joy_msg = "Button {} value: {}".format(self.button_name, self.button_value)

        self.pub.publish(joy_msg)

        
def main():

    node =JoyNode()

    while not rospy.is_shutdown():

        res = node.getJoyInput()

        if res :

            node.pushJoyOutput()

        else:

            print("error2")

        node.rate.sleep()


if __name__ == '__main__':

    main()

