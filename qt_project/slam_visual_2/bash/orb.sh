#! /bin/bash

export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:~/slam/ORB_SLAM2/Examples/ROS
export LD_LIBRARY_PATH=/home/ubuntu/slam/ORB_SLAM2/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/g2o/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/DBoW2/lib:$LD_LIBRARY_PATH;
echo "export done ..."
echo "rosrun ..."
rosrun ORB_SLAM2 Stereo /home/ubuntu/slam/ORB_SLAM2/Vocabulary/ORBvoc.txt /home/ubuntu/slam/ORB_SLAM2/Examples/Stereo/EuRoC.yaml false /camera/left/image_raw:=/zed/zed_node/left_raw/image_raw_color /camera/right/image_raw:=/zed/zed_node/right_raw/image_raw_color

