/*
 *  dvrk_move_test_translate.cpp
 *
 *	Author(s): Tamas D. Nagy
 *	Created on: 2016-10-10
 *
 */

#include <ros/ros.h>
#include <ros/package.h>
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>
#include "dvrk/arm.hpp"
#include "dvrk/psm.hpp"
#include "dvrk/pose.hpp"
#include "dvrk/trajectory_factory.hpp"


int main(int argc, char **argv)
{

	// Check command line arguments
	if (argc < 5) 
	{
		std::cout << 
		"Use with params: PSM1/PSM2; init_pos/no_init_pos; rate; speed" 
		<< std::endl;
		return 1;
	}
	
	std::istringstream ss1(argv[3]);
	int rate_command;
	ss1 >> rate_command;
	
	std::istringstream ss2(argv[4]);
	double speed;
	ss2 >> speed;	
		
	double dt = 1.0/ rate_command;
	dvrk::Trajectory<double> to_enable_cartesian;
	dvrk::Trajectory<dvrk::Pose> circle_tr;
	
	
	// Initialize ros node
    ros::init(argc, argv, "irob_dvrk_move_test");
    ros::NodeHandle nh;
    
    // Robot control
  	try {
    	dvrk::PSM psm(nh, dvrk::ArmTypes::typeForString(argv[1]),
    		dvrk::PSM::ACTIVE);
    	ros::Duration(1.0).sleep();
    	//psm.home(); 
		// Init position if necessary
		if (std::string(argv[2]) == "init_pos")
		{
			// init
			ROS_INFO_STREAM("Going to init position...");
			psm.setRobotState(dvrk::PSM::STATE_POSITION_JOINT);
			int init_joint_idx = 2;
			to_enable_cartesian = 
   				dvrk::TrajectoryFactory::
   					linearTrajectoryWithSmoothAcceleration(
   						psm.getJointStateCurrent(init_joint_idx), 
   						0.07,
   						1.0/speed, 0.3/speed, dt);
 			
			psm.playTrajectory(init_joint_idx, to_enable_cartesian);
   	 		
   		}
  
   	
   		// Do preprogrammed movement
   		ROS_INFO_STREAM("Starting programmed movement...");
   		ROS_INFO_STREAM("Loop rate:\t" << rate_command << " Hz");
   		ROS_INFO_STREAM("Speed:\t"<< speed);
   	
   	 	psm.setRobotState(dvrk::PSM::STATE_POSITION_JOINT);

    	ros::Duration(0.5).sleep();
		
		   	
    	// translation
    	/*int joint_idx = 2;	
    	int r_joint_idx = 3;	
    	double x1 = 0.1089;
    	double x2 = 0.17;
    	double r1 = 1.0; 
    	double r2 = -1.0;
    	double T = 5.0/speed;
    	double Tacc = T*0.1;*/
    	
    	// translation x
    	int joint_idx = 0;
    	
    	double x1 = -0.868;
    	double x2 = -0.328;
    	
    	double T = 5.0/speed;
    	double Tacc = T*0.2;
    	
    	   	 
    	// Move
    	ROS_INFO_STREAM("Going to start position...");	
    	
    	psm.setRobotState(dvrk::PSM::STATE_POSITION_JOINT);
    	dvrk::Trajectory<double> 
    		init_tr(dvrk::TrajectoryFactory::
    			linearTrajectoryWithSmoothAcceleration(
    				psm.getJointStateCurrent(joint_idx), 
					x1,
					T, Tacc, dt)); 
    	
  
	
		dvrk::Trajectory<double> 
			back_tr(dvrk::TrajectoryFactory::
				linearTrajectoryWithSmoothAcceleration(
					x2,
					x1,
					T, Tacc, dt));
					
		dvrk::Trajectory<double> 
    		to_tr(dvrk::TrajectoryFactory::
    			linearTrajectoryWithSmoothAcceleration(
    				x1,
					x2,
					T, Tacc, dt));
	
					
    	//psm.playTrajectory(r_joint_idx, r_init_tr);	
    	psm.playTrajectory(joint_idx, init_tr);
    	
    	ros::Duration(0.5).sleep();
    	
   
    		
    	auto start = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double> elapsed;
    	std::chrono::duration<double> testT(30.0);
     
   	    while(ros::ok()) {
			//
			elapsed =
	 			std::chrono::high_resolution_clock::now()-start;
	 		ROS_INFO("Time elapsed: %f s", (elapsed));
	 		if (elapsed >= testT)
	 			break;		
   	    	ROS_INFO_STREAM("Going to position 1...");	
    		
    		psm.playTrajectory(joint_idx, to_tr);
    		//
    		elapsed =
	 			std::chrono::high_resolution_clock::now()-start;
	 		ROS_INFO("Time elapsed: %f s", (elapsed));
	 		if (elapsed >= testT)
	 			break;	
    		
    		ros::Duration(0.5).sleep();
    		
    		//
    		elapsed =
	 			std::chrono::high_resolution_clock::now()-start;
	 		ROS_INFO("Time elapsed: %f s", (elapsed));
	 		if (elapsed >= testT)
	 			break;	
    		ROS_INFO_STREAM("Going to position 2...");	
    		
    		psm.playTrajectory(joint_idx, back_tr);
    		//
    		elapsed =
	 			std::chrono::high_resolution_clock::now()-start;
	 		ROS_INFO("Time elapsed: %f s", (elapsed));
	 		if (elapsed >= testT)
	 			break;	
    		
    		ros::Duration(0.5).sleep();
    	}
    	
    	ROS_INFO_STREAM("Test done going to final position...");	
    	
			
		dvrk::Trajectory<double> 
			fin_tr(dvrk::TrajectoryFactory::
				linearTrajectoryWithSmoothAcceleration(
					psm.getJointStateCurrent(joint_idx), 
					x1,
					T, Tacc, dt));
					
					 	
		psm.playTrajectory(joint_idx, fin_tr);	
    
    	//psm.home();
    	ROS_INFO_STREAM("Program finished succesfully, shutting down ...");
    	
    } catch (const std::exception& e) {
  		ROS_ERROR_STREAM(e.what());
  		ROS_ERROR_STREAM("Program stopped by an error, shutting down ...");
  	}
    
    
    // Exit
    ros::shutdown();
	return 0;
}



