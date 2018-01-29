//Sam and Katie's Ninja Code
#pragma config(Sensor, S1,     soundSensor,    sensorSoundDB)

//define varibles and functions called in program
void forward(int inspeed);
int move_scan();
void rotate(int inspeed, int ticks);
void stops();
void colourSense();
int soundSense(int Nspeed);
void faceSly();
void faceScared();

task main()
{
	//defining variables
	float distance;
	int value;
	int speed=30;
	int forwardTicks=1000;
	int rotateTicks=175;
	int colorRead;
	int locs[4][4]={{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}};

	//setting the motor speed
	setMotorSpeed(motorB, speed);
	setMotorSpeed(motorC,speed);

	//setting infinite loop
	while(true)
	{
		//moving forward
		//scanning the area infront
		int move_result = move_scan();
		if (speed==30)
		{
			faceSly();
		}
		else if (speed==15)
		{
			faceScared();
		}
		//moving forward
		forward(speed);
		colourSense();
		speed=soundSense(speed);
		//scanning infront of self
		move_result = move_scan();
		//if there is an object infront, 1 is returned
		if (move_result == 1)
		{
			rotate(speed, rotateTicks);
		}
	}
}
//definging functions
int move_scan()
{
	SensorType[S3] = sensorEV3_Ultrasonic;
	float distance;
	distance=getUSDistance(S3);
	if (distance>=0 && distance<=40)
	{
		return (1);
	}
	return(0);
}

void forward(int inspeed)
{
	//move forward
	setMotorSpeed(motorC,inspeed);
	setMotorSpeed(motorB,inspeed);
	wait1Msec(2000);
}

void stops()
{
	//move forward
	setMotorSpeed(motorC,0);
	setMotorSpeed(motorB,0);
	wait1Msec(1500);
}

void rotate(int inspeed, int ticks)
{
	//turn
	moveMotorTarget(motorC,ticks,inspeed);
	moveMotorTarget(motorB,ticks,-inspeed);
	waitUntilMotorStop(motorC);
	waitUntilMotorStop(motorB);
}

void colourSense()
{
		SensorType[S4] = sensorEV3_Color;
		SensorMode[S4] = modeEV3Color_Color;
		int colorInput = 1;
		wait1Msec (1000);
		colorInput = getColorName(S4);// function to read color sensor and return measured color value
		wait1Msec (1000);

	if (colorInput == colorNone)
	{
		wait1Msec(1000);
	}

	else if (colorInput == colorRed)
	{
		setLEDColor(ledRed);
		wait1Msec(1000);
	}
	else if (colorInput == colorYellow)
	{
		setLEDColor(ledOrange);
		wait1Msec(1000);
	}
	else if (colorInput == colorGreen)
	{
		setLEDColor(ledGreen);
		wait1Msec(1000);
	}
	else if (colorInput == colorBlue)
	{
		setLEDColor(ledGreenPulse);
		wait1Msec(1000);
	}
}

int soundSense(int Nspeed)
{
	int soundVolume;
	soundVolume=SensorValue(soundSensor);

	if(soundVolume >= 30)
	{
		Nspeed=15;
	}
	else if	(soundVolume < 30)
	{
		Nspeed=30;
	}

	return (Nspeed);
}

void faceSly()
{

	int ROWS =18;
	int COLS =18;
	int i = 0;
	int j = 0;

//creating the 'face' array
	char pixels [18][18] =
	{	{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
		{	1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
		{	1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0},
		{	1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0},
		{	1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0},
		{	0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
		{	0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
		{	0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


	for(i = 0; i<(ROWS); i++)
	{
		for(j=0; j<(COLS); j++)
		{
			if(pixels[i][j]==0)
				clearPixel((j)*4 + 50,127-(20 + (i)*4));

			else if (pixels [i][j]==1)
				setPixel ((j)*4 + 50, (127 - (20 + (i)*4)));
		}
	}
}

void faceScared()
{

	int ROWS =18;
	int COLS =18;
	int i = 0;
	int j = 0;

	char pixels [18][18] =
	{	{	0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0},
		{	0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0},
		{	0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
		{	0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
		{	0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
		{	0,1,1,0,1,1,1,1,0,0,0,1,1,0,1,1,1,1},
		{	0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
		{	0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0},
		{	0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
		{	0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
		{	0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
		{	0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
		{	0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
		{	0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0}};

	for (i = 0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
			if(pixels[i][j]==0)
				clearPixel((j)*4 + 50,127-(20 + (i)*4));

			else if (pixels [i][j]==1)
				setPixel ((j)*4 + 50, 127-(20 + (i)*4));
		}
	}
}
