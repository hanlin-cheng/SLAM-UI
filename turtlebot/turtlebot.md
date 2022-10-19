- # 1.先完成ROS melodic安装

-  

- # 2.安装依赖：

- ```
  $ sudo apt-get install libusb-dev
  $ sudo apt-get install libspnav-dev
  $ sudo apt-get install ros-melodic-joystick-drivers
  $ sudo apt-get install bluetooth
  $ sudo apt-get install libbluetooth-dev
  $ sudo apt-get install libcwiid-dev
  ```

- 

- 

- # 3.新建工作空间，准备相关包

- ```
  $ mkdir -p ~/turtlebot_ws/src 
  $ cd ~/turtlebot_ws/src 
  $ git clone https://github.com/turtlebot/turtlebot_simulator
  $ git clone https://github.com/turtlebot/turtlebot.git
  $ git clone https://github.com/turtlebot/turtlebot_apps.git
  $ git clone https://github.com/udacity/robot_pose_ekf
  $ git clone https://github.com/ros-perception/depthimage_to_laserscan.git 
  $ git clone https://github.com/yujinrobot/kobuki_msgs.git
  $ git clone https://github.com/yujinrobot/kobuki_desktop.git
  $ cd kobuki_desktop/
  $ rm -r kobuki_qtestsuite
  $ git clone https://github.com/toeklk/orocos-bayesian-filtering.git
  $ git clone https://github.com/turtlebot/turtlebot_msgs.git
  $ git clone https://github.com/ros-drivers/joystick_drivers.git
  ```

-  

- # 4.复制kobuki和yujin_ocs依赖库到turtlebot_ws/src工作空间下

- ```
  $ mkdir -p ~/repos/
  $ cd ~/repos/
  $ git clone https://github.com/yujinrobot/kobuki.git
  $ cp -r kobuki/* ~/turtlebot_ws/src/
  $ git clone https://github.com/yujinrobot/yujin_ocs.git
  $ cp -r yujin_ocs/yocs_cmd_vel_mux/ yujin_ocs/yocs_controllers ~/turtlebot_ws/src/
  ```

-  

- # 5.编译工作空间

- ```
  $ cd ~/turtlebot_ws
  $ catkin_make
  ```

-  

- 遇到问题：

- ![image-20220125152153849](C:\Users\hanlin\AppData\Roaming\Typora\typora-user-images\image-20220125152153849.png)

- 

-  

- 解决方法：orocos-bfl没有安装。

- ```
  sudo apt-get install ros-melodic-bfl
  ```

- 注意自己ros版本的选择。安装后再catkin_make。

-  

- # 6.添加工作空间到bashrc文件

- ```
  echo "source ~/turtlebot_ws/devel/setup.bash" >> ~/.bashrc
  source ~/.bashrc
  ```

- 

- # 7.测试

- ```
  roslaunch turtlebot_bringup minimal.launch
  ```

- 

- 问题：cannot launch node of type [laptop_battery_monitor/laptop_battery.py]: laptop_battery_monitor

- 解决：

- ```
  sudo apt-get install ros-melodic-laptop-battery-monitor
  ```

- 