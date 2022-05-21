
//Declare initial variables and parametrs

//X axis 
const int DIRX = 4;
const int STEPX = 5;

//Y axis
const int DIRY = 6;
const int STEPY = 7;

//Z axis
const int DIRZ = 8;
const int STEPZ = 9;

//Tool control
const int TOOL = 10;

//Steps per revolution
const int  steps_per_rev = 200;

//Steps per millimiter for each axis
const int steps_per_mmX = 0;
const int steps_per_mmY = 0;
const int steps_per_mmZ = 0;

//Homing pins
const int homing_x_0 = 1;
const int homing_y_0 = 2;
const int homing_z_0 = 3;
const int homing_x_1 = 11;
const int homing_y_1 = 12;
const int homing_z_1 = 13;

//Other parameters
const int motor_frequency = 50;

const int steps_per_mmX = 50;
const int steps_per_mmY = 50;
const int steps_per_mmZ = 50;

void setup()
{
    //Setup motor period to enforce motor frequency
    int motor_period = 1000/motor_frequency;

    //Start serial connection of 115,200 bauds
    Serial.begin(115200);
    
    //Setup all output pins
    pinMode(STEPX, OUTPUT);
    pinMode(DIRX, OUTPUT);
    pinMode(STEPY, OUTPUT);
    pinMode(DIRY, OUTPUT);
    pinMode(STEPZ, OUTPUT);
    pinMode(DIRZ, OUTPUT);
    pinMode(TOOL, OUTPUT);

    //Setup all input pins
    pinMode(homing_x_0, INPUT);
    pinMode(homing_y_0, INPUT);
    pinMode(homing_z_0, INPUT);
    pinMode(homing_x_1, INPUT);
    pinMode(homing_y_1, INPUT);
    pinMode(homing_z_1, INPUT);
}

void loop()
{
    return;
}

void moveX(int coord)
