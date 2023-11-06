#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <sys/select.h>
#endif

/*#define BURGER_MAX_LIN_VEL 0.22
#define BURGER_MAX_ANG_VEL 2.84
#define WAFFLE_MAX_LIN_VEL 0.26
#define WAFFLE_MAX_ANG_VEL 1.82
#define LIN_VEL_STEP_SIZE 0.01
#define ANG_VEL_STEP_SIZE 0.1*/


geometry_msgs::TwistStamped _input;
int key = getchar();

int getcher() {
   static struct termios oldt,newt;
   tcgetattr( STDIN_FILENO, &oldt );    //save old setting
   newt = oldt;
   newt.c_lflag &= ~(ICANON);
   tcsetattr( STDIN_FILENO, TCSANOW, &newt );

   tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
   return key;
}

int input_key(){

    _input.twist.linear.x = 0;
    _input.twist.angular.z = 0.0;

    switch (key)
    {
        case 'f':
            _input.twist.linear.x =  _input.twist.linear.x + 0.1;
            break;
        case 'b':
            _input.twist.linear.x =  _input.twist.linear.x - 0.1;
            break;
        case 'r':
            _input.twist.angular.z = _input.twist.angular.z - 1.0;
            break;
        case 'l':
            _input.twist.angular.z = _input.twist.angular.z + 1.0;
            break;
    }
}


int main(int argc, char **argv)
{
   ros::init(argc, argv, "bs_teleop");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::TwistStamped>("bs_input", 100);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        char key = getcher();

        if(key > 0){
             input_key();
        }

        if( key == 'q') break;

        pub.publish(_input);
        loop_rate.sleep();
    }
    return 0;
    
}