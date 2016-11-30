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
    - x: 	(-0.226, 0.2188)
    - y: 	(0.161, -0.178)
   	- z: 	(-0.04, -0.2222)
  - HW and simulator coordinate systems are compatible and matching
      
![alt tag](docs/PSM_coordinates.png)
