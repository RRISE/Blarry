#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * This is copied from 2015 recycle rush robot
 *
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

const int NORMSPEED = 80;	//% speed of normal driving
const int MAXSPEED = 100;

/* robot physical dimension */
const float ROBOT_WIDTH = 2.0f;	//robot width in meters

/* joysticks and buttons */
//Logitech joystick
const int LOGITECH_TRIGGER = 1;
const int LOGITECH_BTN2 = 2;
const int LOGITECH_BTN3 = 3;
const int LOGITECH_BTN4 = 4;
const int LOGITECH_BTN5 = 5;
const int LOGITECH_BTN6 = 6;
//xbox 360 controller buttons
const int XBOX_BTN_A = 1;
const int XBOX_BTN_B = 2;
const int XBOX_BTN_X = 3;
const int XBOX_BTN_Y = 4;
const int XBOX_BUMPER_L = 5;
const int XBOX_BUMPER_R = 6;
const int XBOX_BTN_BACK = 7;
const int XBOX_BTN_START = 8;
//Xbox 360 controller joysticks
const int XBOX_L_XAXIS = 0;
const int XBOX_L_YAXIS = 1;
const int XBOX_L_TRIGGER = 2;
const int XBOX_R_TRIGER = 3;
const int XBOX_R_XAXIS = 4;
const int XBOX_R_YAXIS = 5;

/* Port allocation */
//Joystick ports
const int LOGITECH_PORT = 0;
const int XBOX0_PORT = 0;
const int XBOX1_PORT = 1;

//motor controller ports
const int TALON_1_PORT = 1;
const int TALON_2_PORT = 2;
//talons 3 and 4 are only in the ArmControl (and don't have to be here)
const int TALON3_CAN_ID = 3;
const int TALON4_CAN_ID = 4;
//talons 5 and 6 are only in the BinControl (and don't need to be here)
//const int TALON_TWISTER_CAN_ID = 5;
//const int TALON_PULLEY_CAN_ID = 6;

//sensor ports
const int GYRO1_PORT = 0;
const int ENCODER1_A_PORT = 2;
const int ENCODER1_B_PORT = 3;
const int ENCODER2_A_PORT = 1;
const int ENCODER2_B_PORT = 0;
//const int LEFT_ARM_SWITCH_PORT = 4;	//the TR Electronics sensors
//const int RIGHT_ARM_SWITCH_PORT = 5;
//const int TOP_LIMIT_SWITCH_PORT = 6;


//sensor config values
const double ENCODER_DIST_PER_PULSE = 0.1665; //Note: this will not work at high speeds. The robot will overshoot.
const double GYRO_SENSITIVITY = 0.007; // "Our gyro is ADRSX622 , with a sensitivity of 7 mV/degree/sec" --Mr.Harwood

/* other */
//math const
const float PI = 3.14159f;

#endif


