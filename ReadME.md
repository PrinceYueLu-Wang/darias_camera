# Camera Parts for Darias Robot Arm

## Introduction
---

This package transfer intel realcamera's depth info into simplfied octomap and publish pointclouds and octree messages. Meanwhile it would automatically eliminate points ,which belon to robots' arms, that would benefit the afterprocessing in obstacle avoidence.

## Contents
- [Package dependencies](ReadME_detailed.md)
- [Description for RosNodes](ReadME_detailed.md)
- [Description for ROStopics](ReadME_detailed.md)
- [Description for Messages](ReadME_detailed.md)
- [Usage](#Usage)
- [MessageUsage](#MessageUsage)

## Usage
---
### Download:

- run ```git clone https://github.com/PrinceYueLu-Wang/darias_camera.git```

- create new branch with name like *test* and switch to remoter branch `julen`
  
- run ```git checkout -b test origin/julen```

---
### Build
- if there were build cache errors, in catkin workingspace run :  ```rm rf ./build ./devel```
- in catkin workingspace run : ```catkin_make```
---
### ROSLaunch

roslaunch files for use:
- src/darias_intelcamera/launch/real_with_tfadjust_allinone.launch
- src/darias_intelcamera/launch/real_with_tfadjust.launch

*real_with_tfadjust_allinone* :   combined three nodes into one node.
*real_with_tfadjust*          :  run three nodes seperately

It is recommended to use the ***allinone*** launch file

---
### Run

- put commands in terminal : ```ros_remote``` to apply configurations of ROS_HOST and ROS_IP 
  - `$ ros_remote`
- in catkin workingspace folder source rospkg file
  - `$ source ./devel/setup.bash`

- in terminal run :
  -  ```$ roslaunch darias_intelcamera real_with_tfadjust_allinone.launch```
---

## MessageUsage
due to ros doesn't offer appropriate 3d points array, the final filtered 3d coordinates of the obstacles would be published in self-defined message type `darias_intelcamera/maplist` .

following part introdues how to used this message in other ros package.  

---
### when rospkg is not created
- source rospkg `darias_intelcamera` to ensure catkin could find it
  - `$ source xxx/darias_camera/devel/setup.bash`
- add rospkg dependency `darias_intelcamera`

  - `$ catkin_creat xxxpkg rospy roscpp darias_intelcamera`

---
### when rospkg is already created
- in `CMakeList.txt` change `find_package`
    ```
    find_package(catkin REQUIRED COMPONENTS
    darias_intelcamera
    xxx
    xxx)
    ```
- in `package.xml` add three following item
  ```
    <build_depend>darias_intelcamera</build_depend>
    <build_export_depend>darias_intelcamera</build_export_depend>
    <exec_depend>darias_intelcamera</exec_depend>
  ```
---
### Pyhton File
import msg lib `from darias_intelcamera.msg import maplist`

specific definition of msgs please turn to [Description for Messages](ReadME_detailed.md)
for exmaple:
```
#!/home/yifei/anaconda3/envs/light36/bin/python
from darias_intelcamera.msg import maplist
import rospy  

class Node(object):
    def __init__(self) -> None:
        rospy.init_node('test', anonymous=True)
        self.pub = rospy.Publisher('talker', maplist, queue_size=10)
        self.rate = rospy.Rate(10) # 10hz
    
    def run(self):       
         while not rospy.is_shutdown():
            msg = rospy.wait_for_message("/camera_visual/filtered/point3d",maplist)
            rospy.loginfo("msg has {} points!".format(len(msg.center_x)) )
            rospy.loginfo("msg type {} points!".format(type(msg.center_x)) )
            self.rate.sleep()
```