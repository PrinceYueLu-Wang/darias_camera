import rospy

import numpy as np

from darias_intelcamera import maplist

from geometry_msgs import Point


class APF_Force():

    def __init__(self):

        pass



class APF():

    def __init__(self):

        rospy.init_node('listener', anonymous=True)

        self.loop_rate = rospy.Rate(10)

        self.obj_num = 1 

        self.obstacles_position= []

        self.obstacles_num = 0

        self.objects_position = np.array(self.obj_num,3)

        self.map_subscriber = rospy.Subscriber(name = "/camera/octomap_list",
                                               data_class=maplist,
                                               callback=self.mapInfoUpdate)


        self.isNewRosMsg = False


    def mapInfoUpdate(self,msg):

        self.obstacles_num = msg.cube_number

        self.obstacles_position = np.zeros(shape=(self.obstacles_num,3))

        self.obstacles_position[:,0] = msg.center_x.reshape(-1,1)
        self.obstacles_position[:,1] = msg.center_y.reshape(-1,1)
        self.obstacles_position[:,2] = msg.center_z.reshape(-1,1)

        self.isNewRosMsg = True


    def dist2Obstacle(self):

        # self.objects_position -> Size :  n * 3
        # self.obstacles_position -> Size :  m * 3
        # dist_matrix -> Size : n * m
        # dist_matrix[i,j] means the distance between the i-th object and the j-th obstacle 

        vectordiff = self.objects_position[:,None,:] - self.obstacles_position

        self.dist_matrix = np.sqrt(np.einsum('ijk,ijk->ij',vectordiff,vectordiff))


    def forceFromField(self):

        idx_min = np.argmin(self.dist_matrix,axis=1)
        dist_min = np.min(self.dist_matrix,axis=1)
    
    def forceMsgUpdate(self):

        pass
    

    def forceMsgPush(self):

        pass






    







