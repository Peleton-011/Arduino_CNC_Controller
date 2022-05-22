
//Declare initial variables and parametrs

//Step
const int STEPS[3] = {5, 7, 9};

//Dir
const int DIRS[3] = {4, 6, 8};

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

//Homing functions
int homing(int axis)
{
    int step_count = 0;

    if (default_direction_cc[axis])
    {
        digitalWrite(DIRS[axis], LOW);        
    }
    else
    {
        digitalWrite(DIRS[axis], HIGH);
    }
    
    while (digitalRead(homing_pins[axis]) == 0)
    {
        digitalWrite(STEPS[axis], HIGH);
        delayMicroseconds(motor_period);
        digitalWrite(STEPS[axis], LOW);
        delayMicroseconds(motor_period);
    }
    
    if (!default_direction_cc[axis])
    {
        digitalWrite(DIRS[axis], LOW);        
    }
    else
    {
        digitalWrite(DIRS[axis], HIGH);
    }

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

void loop()
{
    return;
}

void moveX(int coord)
