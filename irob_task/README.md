# irob-dvrk-automation

Timing:
  - dVRK bridge: ~1 kHz
  - Time for one command in ROS: 80 - 160 us
  
PSM workspace:
  - joints:
  	- #0 outer_yaw (rad): 			(-1.3, 1.3)
  	- #1 outer_pitch (rad): 		(-0.8, 0.8)
  	- #2 outer_insertion (m): 		(0.0, 0.24) enable cartesian: > 0.05
  	- #3 outer_roll (rad): 			(-2.8, 2.8)
  	- #4 outer_wrist_pitch (rad): 	(-1.3, 1.3)
  	- #5 outer_wrist_yaw (rad): 	(-1.3, 1.3)
  	- #6 jaw (rad): 				(0.0, 1.3)
  - cartesian  (in meters):
    - origin: cannula center point
      - x: (-0.215, 0.215)
      - y: (-0.175, 0.160)
      - z: (-0.040, -0.222)
  - HW and simulator coordinate systems are compatible and matching
  
Using cv-camera:
  - sudo apt-get install ros-kinetic-cv-camera
  - usage: http://wiki.ros.org/cv_camera
  - device ID is based on the connection order of the cameras
  - sudo apt-get install ros-kinetic-camera-calibration
  - http://wiki.ros.org/camera_calibration/Tutorials/StereoCalibration
  - http://wiki.ros.org/stereo_image_proc
  - stereo camera calibrations must be saved from separate files 
  	(elsehow the disparity will be extremely noisy)
  - use the calibration app with option --approximate=0.1
  
Raspberry:
  - Ubuntu + ROS kinetic: 
  	http://www.german-robot.com/2016/05/26/raspberry-pi-sd-card-image/
  - Rospicam node: https://github.com/UbiquityRobotics/raspicam_node
    - sudo sh -c 'echo "deb https://packages.ubiquityrobotics.com/ubuntu/ubiquity xenial main" > /etc/apt/sources.list.d/ubiquity-latest.list'
    - sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key C3032ED8
    - sudo apt-get update
    - sudo apt install ros-kinetic-raspicam-node
  
ROS network setup:
  - fix ip: 192.168.1.104 255.255.255.0 192.168.1.1
  - DNS: 8.8.4.4
  - /etc/hosts: 
  				192.168.1.104	master
				192.168.1.105	left-pi
				192.168.1.106	right-pi
  - export ROS_HOSTNAME, ROS_IP, ROS_MASTER_URI
  - see http://elinux.org/RPi_Setting_up_a_static_IP_in_Debian
      
![alt tag](docs/PSM_coordinates.png)