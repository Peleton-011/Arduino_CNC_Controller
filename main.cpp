//#include <stdint.h>
#include <SPI.h>
#include <SD.h>
#include <TFT.h>

//Declare initial variables and parametrs

//Step
const int STEPS[3] = {5, 6, 9};

//Dir
const int DIRS[3] = {4, 7, 8};

//Tool control
const int TOOL = 10;

//Steps per revolution
const int  steps_per_rev = 200;

//Steps per millimiter for each axis
const int steps_per_mm[3] = {0, 0, 0};

//Homing pins
const int homing_pins[6] = {1, 2, 3, 11, 12, 13};

//Other parameters
const int motor_frequency = 50;

const int actuation_length = 500;

const int axes = 3;

//Default spinning directions. Should be determined through testing
const bool default_direction_cc[3] = {true, true, true};

//Range of action
int range[3];

//Current position in steps
int pos[3];

//Setup motor period to enforce motor frequency
int motor_period = 1000/motor_frequency;

void setup()
{
    //Start serial connection of 115,200 bauds
    Serial.begin(115200);
    
    //Setup all output pins
    for (int i = 0; i < axes; i++)
    {
        pinMode(DIRS[i], OUTPUT);
        pinMode(STEPS[i], OUTPUT);
    }
    
    pinMode(TOOL, OUTPUT);

    //Setup all input pins
    for (int i = 0; i < (axes * 2); i++)
    {
        pinMode(homing_pins[i], INPUT);
    }


    //Homing and initial position
    for (int i = 0; i < axes; i++)
    {
        range[i] = homing(i);
        pos[i] = range[i];
    }
}

//Set turning direction, if opposite is false it will be the default direction for that axis
//otherwise it will be the other direction
void setDirection(int axis, bool opposite)
{
    if (!opposite)
    {
        if (default_direction_cc[axis])
        {
            digitalWrite(DIRS[axis], LOW);
            return;
        }

        digitalWrite(DIRS[axis], HIGH);
        return;
    }
    
    if (!default_direction_cc[axis])
    {
        digitalWrite(DIRS[axis], LOW);        
        return;
    }
    digitalWrite(DIRS[axis], HIGH);
    return;
}

//Homing function
int homing(int axis)
{
    int step_count = 0;

    setDirection(axis, false);
    
    while (digitalRead(homing_pins[axis]) == 0)
    {
        digitalWrite(STEPS[axis], HIGH);
        delayMicroseconds(motor_period);
        digitalWrite(STEPS[axis], LOW);
        delayMicroseconds(motor_period);
    }
    
    setDirection(axis, true);

    while (digitalRead(homing_pins[3]) == 0)
    {
        digitalWrite(STEPS[axis], HIGH);
        delayMicroseconds(motor_period);
        digitalWrite(STEPS[axis], LOW);
        delayMicroseconds(motor_period);

        step_count++;
    }

    return step_count;
} 

//Move to coords and use the tool there function
void moveAndTool(int coordX, int coordY)
{
    move(coordX, 0);
    move(coordY, 1);
    useTool();
}

//Generic function to move a specific axis to a specific position
void move(int coord, int axis)
{
    int distance = pos[axis] - coord;
    //Return if the distance is 0
    if (!distance)
    {
        return;
    }
    
    setDirection(axis, (distance > 0));

    while (!!distance)
    {
        //Move a step
        digitalWrite(STEPS[axis], HIGH);
        delayMicroseconds(motor_period);
        digitalWrite(STEPS[axis], LOW);
        delayMicroseconds(motor_period);

        //Update position
        if (distance > 0)
        {
            pos[axis]++;
        }
        else if (distance < 0)
        {
            pos[axis]--;
        }
        else //Return if the position is reached
        {
            return;
        }

        //Update distance
        distance = pos[axis] - coord;
    }
}

//Function that uses tool whichever the current coordinates
void useTool()
{
    digitalWrite(TOOL, HIGH);
    move(range[3], 3);
    delayMicroseconds(actuation_length);
    move(0, 3);
    digitalWrite(TOOL, LOW);
}

//Read a number of bytes from a file
int32_t readNbytesInt(File *p_file, int position, byte nBytes)
{
    if (nBytes > 4)
        return 0;

    p_file->seek(position);

    int32_t weight = 1;
    int32_t result = 0;
    for (; nBytes; nBytes--)
    {
        result += weight * p_file->read();
        weight <<= 8;
    }
    return result;
}

void loop()
{
    return;
}
