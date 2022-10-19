#!/bin/bash

echo "press passward"
echo "ubuntu" | sudo -S netstat -tlnp
sudo chmod 777 /dev/ttyUSB*
echo "runing IMU..."
source ~/xsens_ws/devel/setup.bash
roslaunch xsens_mti_driver xsens_mti_node.launch
