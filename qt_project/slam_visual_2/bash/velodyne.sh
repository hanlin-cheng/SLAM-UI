#! /bin/bash
#export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:/home/ubuntu/turtlebot_ws/src/velodyne/
source /opt/ros/melodic/setup.bash
source ~/turtlebot_ws/devel/setup.bash
echo "runing ..."
roslaunch velodyne_pointcloud velodyne_vlp16.launch
#roslaunch velodyne_pointcloud VLP16_points.launch
