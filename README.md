# 1.Prerequisites

我们在xavier上基于ubuntu18.04进行成功测试，需要提前配置好以下环境条件。

## C++11

需要使用到c++11的部分特性

## Opencv

我们需要使用opencv>=3.4.0

http://opencv.org

## Turtlebot2

利用turtlebot移动机器人作为移动底盘，参考安装说明文档进行安装，位于turtlebot文件夹。

## Velodyne

使用16线激光雷达用于lio-sam

 https://github.com/ros-drivers/velodyne.git

## Xsens

使用Xsens9轴imu

 https://github.com/ros-drivers/velodyne.git

## ZED

使用zed或者zed2相机作为视觉传感器，我们提供的安装说明文档位于zed文件夹。

## Rtabmap

https://github.com/introlab/rtabmap.git

## LIO-SAM

https://github.com/TixiaoShan/LIO-SAM.git

你可以在lio-sam文件夹下找到激光与imu标定之后的文件。

## Orbslam2

https://github.com/raulmur/ORB_SLAM2.git

## Vins-fusion

https://github.com/HKUST-Aerial-Robotics/VINS-Fusion.git

你可以在vins-fusion文件夹下找到视觉与imu的标定文件。

# 2.运行qt终端界面

利用qt creator运行集成算法，源代码位于src文件夹内

