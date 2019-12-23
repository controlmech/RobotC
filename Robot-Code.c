// Check for presence of IR beacon by wiggling the robot to check if the IR beacon is still on
// wiggleSpeed determines the direction of turning and wiggleAngle determines how much to turn
bool checkForIR(int wiggleSpeed, int wiggleAmount)
{
	bool present = false;

	SensorMode[S3] = modeEV3IR_Seeker;

	motor[motorA] = motor[motorD] = 0;

	motor[motorA] = wiggleSpeed;
	motor[motorD] = -wiggleSpeed;
	nMotorEncoder[motorA] = 0;
	while (fabs(nMotorEncoder[motorA]) < wiggleAmount)
	{
		if (SensorValue[S3] != 0)
			present = true;
	}
	motor[motorA] = -wiggleSpeed;
	motor[motorD] = wiggleSpeed;
	while (fabs(nMotorEncoder[motorA]) > 0)
	{
		if (SensorValue[S3] != 0)
			present = true;
	}
	motor[motorA] = motor[motorD] = 0;
	return present;
}

// Operate motor for a certain amount of seconds until
// Assumes IR sensor is in S3 and the physical hitter is motorB
// how to set motor as a parameter??
void operateMotor(int repetitions, int motorSpeed, int motorRotationAmount, bool motorBBool)
{
	int motorNum = 0;
	if (motorBBool)
		motorNum = 1;
	else
		motorNum = 2;
		for (int count = 0; count < repetitions; count ++)
		{
			nMotorEncoder[motorNum] = 0;

			// Move the arm up and down
			motor[motorNum] = -motorSpeed;
			while (nMotorEncoder[motorNum] > -motorRotationAmount)
			{}
			motor[motorNum] = motorSpeed;
			while (nMotorEncoder[motorNum] < 0)
			{}

		}
		motor[motorNum] = 0;
	}




task main()
{
	bool tempPresent = checkForIR(10,50);
	bool present = checkForIR(-10,50);

	if (present || tempPresent)
		present = true;
	motor[motorB] = motor[motorC] = 0;
	SensorType[S3] = sensorEV3_IRSensor;


	bool motorBBool = true;
	// Test operate motor function
	while (present)
	{
		if (present)
		{
			operateMotor(5,50,100, motorBBool);
			tempPresent = checkForIR(10,50);
			present = checkForIR(-10,50);

			if (present || tempPresent)
				present = true;
			else
				present = false;

			motorBBool = !motorBBool;
		}
	}
}
