//ROBOT's QLEARNING FUNCTIONS

float RANDOM(float EXPLORATION_PARAMETER){
  float RANDOM_VARIABLE;
  float PROBABILITY;

  RANDOM_VARIABLE = random(0, 100);
  PROBABILITY = RANDOM_VARIABLE/100;

  return PROBABILITY;

  //THIS FUNCTION IS USED TO REDUCE EPSILON(EXPLORATION PARAMETER) WITH TIME.FINALLY AT THE END YOU GET RID EPSILON AND THE ROBOT LEARNS TO AVOID OBSTACLES ON ITS OWN 
}

float DECAY(float PARAMETER){
  PARAMETER = PARAMETER*0.98;
  return PARAMETER;
}

int GET_STATE(){
  int STATE_NUMBER;
  STATE_NUMBER = random(0, 10);
  return STATE_NUMBER;
}

float MAX(float Q_Table[][4], int NEXT_S){
  
  //THIS FUNCTION FINDS THE BIGGEST NUMBER IN Q_TABLE[NEXT_STATE]. THE MAIN ROLE OF THIS FUNCTION IS TO FIND Q_MAX PARAMETER 
  float LIST[4];
  float N1;
  float N2;
  float MAX_VALUE= 0.0;
  float DIFF; 

  for(int b = 0; b<=3; b++)
     {
      LIST[b] = Q[NEXT_S][b];
     }

  for(int j = 0; j<=2 ; j++)
    {
      if(MAX_VALUE >LIST[j])
        {
          N1 = MAX_VALUE;
        }
      else
        {
         N1 = LIST[j];
        }
         
      N2 = LIST[j+1];
      DIFF = N1- N2;

      if(DIFF > 0)
        {
          MAX_VALUE = N1;
        }

      else
        {
          MAX_VALUE = N2;
        }
    }   
  return MAX_VALUE;
}

void Update(float Q_TABLE[][4] , int S, int NEXT_S, int A, int ACTIONS[], int R, float LEARNING_RATE, float DISCOUNT_FACTOR)
{

  Q_OLD = Q_TABLE[S][A];                        
  Q_MAX = MAX(Q_TABLE, NEXT_S);
  Q_NEW = (1-LEARNING_RATE)*Q_OLD + LEARNING_RATE*(R + DISCOUNT_FACTOR*Q_MAX); 
  Serial.print("Q VALUE : ");
  Serial.println(Q_NEW);
  Q_TABLE[S][A] = Q_NEW;                          
}
