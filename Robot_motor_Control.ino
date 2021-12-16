//Robot actions
void Forward(){
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
}

void Backward(){
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
}

void Left(){
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
}

void Right(){
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
}

void Stop(){
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, LOW);
}

bool Obstacle_Avoider()
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, LOW);
  distance = (duration/2)/29.1;

  if (distance < 13.5){
    Obstacle = true;
  }

  if (distance > 13.5){
    Obstacle = false;
  }

  delay(10);
  return Obstacle;
}

bool Edge_Avoider(){
  read_IRl = digitalRead(IR_l);
  read_IRr = digitalRead(IR_r);

  if (read_IRr == LOW && read_IRl == LOW){
    Forward();
  }
  if (read_IRr == HIGH && read_IRl == HIGH){
    Backward();
    delay(300);
    Right();
    delay(550);
    Forward();
    delay(200);
  }
  if(read_IRr == LOW && read_IRl == HIGH){
    Backward();
    delay(300);
    Right();
    delay(550);
    Forward();
    delay(200);
  }
  if(read_IRr == HIGH && read_IRl == LOW){
   Backward();
   delay(400);
   Left();
   delay(550);
   Forward();
   delay(200);
    }
}

void loop() 
{
 //TRAINING//
  for(int I =0; I<EPOCHS; I++)
  {
    Serial.println("START :");
    ACTION_TAKEN = false;
    FLAG = 0;
       while(true)
          {
            Forward();
            Obstacle = Obstacle_Avoider();
            Edge = Edge_Avoider();
            if(Obstacle == true || Edge == true)
            {
              NEXT_STATE = STATE+1;
              
              if(NEXT_STATE == 10)
                {
                 NEXT_STATE = 0;
                }

               if(NEXT_STATE < 0)
                {
                 NEXT_STATE = 0;
                }
               
              Serial.print("STATE: ");
              Serial.println(STATE);
              FLAG = 1;
              break;
            }
          }
     if(FLAG ==1)
     {
       PROBA = RANDOM(EPSILON);
        if (PROBA<=EPSILON)     //EXPLORE THE ACTIONS 
          {
            ACTION = random(0,4);
            FLAG = 2;
          }
        else                  //EXPLOIT THE ACTIONS FROM Q TABLE
          {
            ACTION = ARGMAX(Q,STATE);
            FLAG = 2;
          }
     }   

     if(FLAG ==2)
     {
         if(ACTION == 0)
         {
          Forward();
          delay(1500);
          Stop();
          REWARD = REWARDS[STATE][ACTION];
         }

         if(ACTION == 1)
         {
          Backward();
          delay(2500);
          Stop();
          REWARD = REWARDS[STATE][ACTION];
         }

         if(ACTION == 2)
         {
          Stop();
          REWARD = REWARDS[STATE][ACTION];
         }

         if(ACTION == 3)
         {
          Left();
          delay(2000);
          Stop();
          REWARD = REWARDS[STATE][ACTION];
         }

        ACTION_TAKEN = true;  
        delay(500); 
     }

   if(ACTION_TAKEN == true)
     {
      Update(Q,STATE,NEXT_STATE,ACTION ,ACTIONS,REWARD,ALPHA ,GAMMA);
      STATE = NEXT_STATE;
      EPSILON = DECAY(EPSILON);
      if(EPSILON<0.5)
       {
        EPSILON  == 0.9;
       }
      Serial.print("EPISODE ENDED : ");
      Serial.println(I);
      delay(7000);
     }       
  }
 //END OF TRAINING//

 //EVALUATION//
 /*USE THIS TO CHECK WHETHER YOUR Q VALUES ARE RIGHT OR WRONG. IF ALL Q VALUES ARE 
 COMING RIGHT OR SEEMS RIGHT/ACCURATE COMMENT THIS SECTION */
 for(int y = 0; y<=9 ; y++)
   {
    Serial.println("SET OF Q VALUES  WILL START:");
    for(int l = 0; l<=3; l++)
      {
        Serial.print("Q VALUE :");
        Serial.println(Q[y][l]);
        delay(2000);
      }
     delay(2000);
   }
   Serial.println("EVALUATION ENDED");
////////////////////////////////END OF EVALUATION/////////////////////////////////////////

////////////////////////////////////////TESTING////////////////////////////////////////////
while(true)
 {
  Forward();
  Obstacle = Obstacle_Avoider();
  Edge = Edge_Avoider();
  if(Obstacle == true || Edge == true)
   {
     STATE = GET_STATE();
     ACTION = ARGMAX(Q,STATE);
     Serial.print("ACTION TAKEN: ");
     Serial.println(ACTION);

     if(ACTION ==0)
      {
        Forward();
        delay(1500);
        Stop();
      }

     if(ACTION == 1)
       {
        Backward();
        delay(1500);
        Stop();
       }
     if(ACTION == 2)
       {
        Stop();
       }

     if(ACTION == 3)
       {
        Left();
        delay(2000);
        Stop();
       }
     }
  }
  //////////////////////////////////////////////////END OF TESTING////////////////////////////////////////////////////////////
}
