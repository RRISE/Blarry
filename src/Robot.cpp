#include "WPILib.h"
#include "RobotMap.h"

class Robot: public IterativeRobot
{

	RobotDrive* pMyRobot = 0; // robot drive system
	CANTalon* pMotorLeft = 0;
	CANTalon* pMotorRight = 0;
	Encoder* pEncoderLeft = 0;
	Encoder* pEncoderRight = 0;
	Gyro* pGyro = 0;

	Joystick* pStick = 0;

	float kP, kI, kD; //PID control
	float turnEncoderTick;

public:
	Robot()
{

		pGyro = new Gyro(GYRO1_PORT);
		pGyro->Reset();
		pGyro->SetSensitivity(GYRO_SENSITIVITY); //magic number used by legendary programmers

		pEncoderLeft = new Encoder(ENCODER1_A_PORT, ENCODER1_B_PORT, false, Encoder::k4X);
		// Defines how far the mechanism attached to the encoder moves per pulse.
		// In this case, we assume that a 360 count encoder is directly attached
		//  to a 3 inch diameter (1.5inch radius) wheel, and that we want to
		//  measure distance in inches.
		//  myEncoder.SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 1.5);
		pEncoderLeft->SetDistancePerPulse(ENCODER_DIST_PER_PULSE); // magic number used by robot last year
		pEncoderLeft->Reset(); //resets values

		pEncoderRight = new Encoder(ENCODER2_A_PORT, ENCODER2_A_PORT, false, Encoder::k4X);
		pEncoderRight->SetDistancePerPulse(ENCODER_DIST_PER_PULSE);
		pEncoderRight->Reset();

		ConfigurePID(1.0f, 0.0f, 0.0f);//this does not change PID of the motors unless you say pMotorLeft->SetPID(kP, kI, kD);

		pMotorLeft = new CANTalon(TALON_1_PORT);
		// This sets the mode of the m_motor. The options are:
		// kPercentVbus: basic throttle; no closed-loop.
		// kCurrent: Runs the motor with the specified current if possible.
		// kSpeed: Runs a PID control loop to keep the motor going at a constant
		//   speed using the specified sensor.
		// kPosition: Runs a PID control loop to move the motor to a specified move sensor position.
		// kVoltage: Runs the m_motor at a constant voltage, if possible.
		// kFollower: The m_motor will run at the same throttle as the specified other talon.
		pMotorLeft->SetControlMode(CANSpeedController::kPosition);
		// This command allows you to specify which feedback device to use when doing
		// closed-loop control. The options are:
		// AnalogPot: Basic analog potentiometer
		// QuadEncoder: Quadrature Encoder
		// AnalogEncoder: Analog Encoder
		// EncRising: Counts the rising edges of the QuadA pin (allows use of a
		//   non-quadrature encoder)
		// EncFalling: Same as EncRising, but counts on falling edges.
		pMotorLeft->SetFeedbackDevice(CANTalon::QuadEncoder);
		// This sets the basic P, I , and D values (F, Izone, and rampRate can also
		//   be set, but are ignored here).
		// These must all be positive floating point numbers (SetSensorDirection will
		//   multiply the sensor values by negative one in case your sensor is flipped
		//   relative to your motor).
		// These values are in units of throttle / sensor_units where throttle ranges
		//   from -1023 to +1023 and sensor units are from 0 - 1023 for analog
		//   potentiometers, encoder ticks for encoders, and position / 10ms for
		//   speeds.
		pMotorLeft->SetPID(kP, kI, kD);

		pMotorRight = new CANTalon(TALON_2_PORT);
		pMotorRight->SetControlMode(CANSpeedController::kPosition);
		pMotorRight->SetFeedbackDevice(CANTalon::QuadEncoder);
		pMotorRight->SetPID(kP, kI, kD);

		pMyRobot = new RobotDrive( pMotorLeft, pMotorRight );
		pMyRobot->SetExpiration(0.1);

		pStick = new Joystick(LOGITECH_PORT);


}
	~Robot()
	{
		delete pMyRobot;
		delete pStick;
		delete pMotorLeft;
		delete pMotorRight;
		delete pEncoderLeft;
		delete pEncoderRight;
	}



private:
	void RobotInit()
	{

	}

	void AutonomousInit()
	{
		pEncoderLeft->Reset();
		pEncoderRight->Reset();
		pGyro->Reset();

		SetupTurnTarget(90.0f); //set target to 90 degrees right
	}

	void AutonomousPeriodic()
	{
		SmartDashboard::PutNumber("Encoder Left Distance", pEncoderLeft->GetDistance());
		SmartDashboard::PutNumber("Encoder Right Distance", pEncoderRight->GetDistance());
		SmartDashboard::PutNumber("Gyro", GetGyroAngle());

		TurnToTarget();
	}

	void TeleopInit()
	{
		pEncoderLeft->Reset();
		pEncoderRight->Reset();
		pGyro->Reset();
	}

	void TeleopPeriodic()
	{
		/*
		float xValue = pStick->GetY(Joystick::kRightHand);

		const float MagicSpeedRatio = 0.1f;
		float speed = xValue * MagicSpeedRatio;

		pMotorLeft->Set(speed);
		pMotorRight->Set(-speed);
		 */
		SmartDashboard::PutNumber("Encoder Left Distance", pEncoderLeft->GetDistance());
		SmartDashboard::PutNumber("Encoder Right Distance", pEncoderRight->GetDistance());
		SmartDashboard::PutNumber("Gyro", GetGyroAngle());

		if(pStick->GetRawButton(1)) {
			DriveToTarget(5.0f * 39.3701f); //39.3701 inches convert to 1 meter
		}
	}




	/****** Extensive Methods ******/

	void ConfigurePID(float P, float I, float D){
		kP = P;
		kI = I;
		kD = D;
	}

	void DriveToTarget(int ticks){
		pMotorLeft->Set(ticks); //encoder ticks
		pMotorRight->Set(ticks);
	}

	float GetGyroAngle(){
		return pGyro->GetAngle();
	}

	void TurnToTarget(){//notice that gyro is not used here
		pMotorLeft->Set(-turnEncoderTick); //encoder ticks
		pMotorRight->Set(turnEncoderTick);
	}

	void SetupTurnTarget(float degree){
		float travelDistance = ROBOT_WIDTH * PI * degree / 360.0f;
		turnEncoderTick = travelDistance * 39.3701f; //meter to inch
	}

};

START_ROBOT_CLASS(Robot);
