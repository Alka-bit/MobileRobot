//Q Learning Parameters 

float ALPHA = 0.1; //Learning Rate, Alpha 
float GAMMA = 0.5; //Discount factor 
float EPSILON = 0.90; //State Exploration parameter 
int REWARD;  //Reward for each actions taken 
int EPOCHS = 150; //No. of Iterations 

int STATE; //Initial state of the robot
int NEXT_STATE; // next state of the robot 
const int STATES = 10; //No. of states in the enviornment 
int ACTION = 0; //Action performed by the robot 
int ACTIONS[4] = {1,2,3,4};
int ACTION_TAKEN = false; //Checks that action is taken or not 
const int NO_OF_ACTIONS = 4; //Possible no. of actions: forward, backward, left, right 

float PROBA; //used for epsilon decay 

float Q[STATES][NO_OF_ACTIONS] = {{0.0,0.0,0.0,0.0},  //MOST IMPORTANT OF ALL IS THE Q TABLE.
                                      {0.0,0.0,0.0,0.0},  //IT IS FORMED BY STATES AS ITS  ROWS 
                                      {0.0,0.0,0.0,0.0},  //AND COLLUMNS AS ITS NUMBER OF ACTIONS
                                      {0.0,0.0,0.0,0.0},  //INITIALISED TO ZERO IN THE START
                                      {0.0,0.0,0.0,0.0},  // THIS WILL UPDATED IN THE FUTURE.
                                      {0.0,0.0,0.0,0.0},
                                      {0.0,0.0,0.0,0.0},
                                      {0.0,0.0,0.0,0.0},
                                      {0.0,0.0,0.0,0.0},
                                      {0.0,0.0,0.0,0.0}};

int REWARDS[STATES][NO_OF_ACTIONS] = {{-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10},
                                      {-10, -2, -1, 10}};

float Q_OLD; //Q Learning Parameters
float Q_NEW;
float Q_MAX;
void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(IR_l, INPUT);
  pinMode(IR_r, INPUT);
  randomSeed(analogRead(A2));
  STATE = 0;
  Serial.println("Training is initializing....");
  delay(5000);
}
