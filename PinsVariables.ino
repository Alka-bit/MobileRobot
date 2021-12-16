//Sensor Pins 

int IR_l = A0; //Left IR Sensor 
int IR_r = A1; //Right IR Sensor 

int TRIG = 8; //ultrasonic 
int ECHO = 9;

int ml1 = 7; //motor
int ml2 = 6;
int mr1 = 5;
int mr2 = 4;

int duration;
float distance;
int FLAG;

int read_IRl = 0; //read IR sesnor inputs 
int read_IRr = 0;

bool Obstacle = false;
bool Edge = false;
