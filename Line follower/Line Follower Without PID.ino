    #define rightMotorForward 3
    #define rightMotorBack 4
    #define PWM_RIGHT 5
    #define leftMotorForward 8
    #define leftMotorBack 9
    #define PWM_LEFT 10
    
   
    int sesor[6]={0};
    int max = 180 ;
  
    void go(int,int);
   void setup()
   {
                  Serial.begin(9600);
                  pinMode(rightMotorForward, OUTPUT);
                  pinMode(rightMotorBack, OUTPUT);
                  pinMode(PWM_RIGHT, OUTPUT);
                  pinMode(leftMotorForward, OUTPUT);
                  pinMode(leftMotorBack, OUTPUT);
                  pinMode(PWM_LEFT, OUTPUT);
                  delay(1500);
                   Serial.begin(9600);
   }
   void loop() 
   {
           for(int i=0; i<6; i++)
          {
              sesor[i]=digitalRead(14+i);
              //Serial.print(sesor[i]);Serial.print("___");
          }
          
        
           int frontsensor = digitalRead(7);
          int leftsensor = digitalRead(6);
          int rightsensor = digitalRead(2);
           Serial.print(frontsensor);
            Serial.print("-----");
          Serial.print(leftsensor);
          Serial.print("-----");
          Serial.print(rightsensor);
          Serial.println("");
          
          if( frontsensor==1)
          {
            go(-(max),max);
             delay(100);
          }
          else if( leftsensor == 1)
          {
               go(-(max+20),max);
          }
          else if( rightsensor == 1)
          {
               go(max,-max);
          }
          
         /* else if((sesor[2]==1)&&(sesor[3]==1))
          {
             go(-(max),max);
             delay(450);
          }
         /* else if(sesor[0]==1)
          {
             go(max,-max);
          }
           else if(sesor[5]==1)
          {
             go(-max,max);
          }
          else if((sesor[0]==1)&&(sesor[1]==1)&&(sesor[2]==1)&&(sesor[3]==1)&&((sesor[4]==0)||(sesor[5]==0)))
          {
             go(-max,max);
             delay(50);
          }
          else if(((sesor[1]==0)&&(sesor[3]==0))||((sesor[2]==0)&&(sesor[4]==0)))
          {
             go(max,-max);
             delay(250);
             max=150;
          }*/
          else
          {
            go(max,max);
          }
   }
void go(int speedLeft, int speedRight) 
{
      if (speedLeft > 0) 
      {
                  digitalWrite(leftMotorForward, HIGH);
                  digitalWrite(leftMotorBack, LOW);
                  analogWrite(PWM_LEFT, speedLeft);
      }
      else 
      {
                  digitalWrite(leftMotorForward, LOW);
                  digitalWrite(leftMotorBack, HIGH);
                  analogWrite(PWM_LEFT, speedLeft);
      }
      if (speedRight > 0) 
      {
                  digitalWrite(rightMotorForward, LOW);
                  digitalWrite(rightMotorBack, HIGH);
                  analogWrite(PWM_RIGHT,( speedRight));       
      }
      else 
      {
                  digitalWrite(rightMotorForward, HIGH);
                  digitalWrite(rightMotorBack, LOW);
                  analogWrite(PWM_RIGHT, (speedRight));           
      }
 }
