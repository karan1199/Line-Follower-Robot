  #include <AFMotor.h>
#include <QTRSensors.h>

    #define NUM_SENSORS             6  // number of sensors used
    #define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
    #define EMITTER_PIN             12  // emitter is controlled by digital pin 2

 int sesor[6]={0};

    // sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
    QTRSensorsAnalog qtra((unsigned char[]) {A5,A4,A3,A2,A1,A0},NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
    unsigned int sensorValues[NUM_SENSORS];

AF_DCMotor motor1(2, MOTOR12_1KHZ ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2(3, MOTOR12_1KHZ ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
  
    unsigned int last_proportional = 0;
     unsigned int lastssproportional = 0;
     unsigned int x=0,a;
    int max = 230 ;
    long integral = 0;
void go(int,int);




    void setup()
   {
      delay(500);
      int i;  
    delay(2000);

    digitalWrite(13, HIGH);    // turn on LED to indicate we are in calibration mode
      for (i = 0; i < 200; i++)  // make the calibration take about 10 seconds
      {
        qtra.calibrate(
          );       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
      }
      Serial.begin(9600);
        
   }
    void loop() {


        unsigned int position = qtra.readLine(sensorValues);
        for(int i=0; i<6; i++)
        {
          sesor[i]=sensorValues[i]<500?1:0;
          Serial.print(sesor[i]);Serial.print("___");
        }
        Serial.println("");
          // The "proportional" term should be 0 when we are on the line.
          int proportional = ((int)position) - 2500;
          Serial.println(proportional);
          /*if((sesor[0]==1)&&(sesor[1]==1))
          {
              x=2;
          }
          else if((sesor[4]==1)&&(sesor[5]==1))
          {
              x=3;
          }
        */
         if((sesor[2]==1)&&(sesor[3]==1)&&(sesor[4]==1)&&(sesor[5]==1))
          {
          max=180;
             go(-(max+30),max);
             delay(250);
          }
          else
          {
            max=200;
          }
          /*if((sesor[0]==1)&&(sesor[1]==1)&&(sesor[2]==1)&&(sesor[3]==1)&&(sesor[4]==1)&&(sesor[5]==1)&&(sesor[6]==1))
          {
          max=150;
             go(-(max+30),max);
             delay(200);
          }
          else
          {
            max=200;
          }*/
       
          if((sesor[0]==0)&&(sesor[1]==0)&&(sesor[2]==0)&&(sesor[3]==0)&&(sesor[4]==0)&&(sesor[5]==0))
          {
            proportional=last_proportional;
             max=120;
            if(proportional >200)
            {
              
              go(max,-(max+60));
              
            }
            else if(proportional <-200)
            
            {
           
              go(-(max+60),max);
            
            }
            else
            {
              delay(300);
               go(-(max+40),max+40);
               delay(200);
            }
           /* else if(proportional <200 && proportional > -200)
           {
            max=125;
              if(x ==2)
            {
              go(max,-(max+30));
            }
            else if(x ==3)
            
            {
              go(-(max+30),max);
        
            }
           }*/
          }
          else
          {
           max=200;
          }
         
          if(max==200)
            {
          // Compute the derivative (change) and integral (sum) of the
          // position.
          int derivative = proportional - last_proportional;
          integral += proportional;

          // Remember the last position.
          last_proportional = proportional;
          if(last_proportional != lastssproportional)
            {
                lastssproportional=last_proportional;
            }
          int power_difference = proportional*0.1+integral*0+ derivative*1;

          // Compute the actual motor settings.  We never set either motor
          // to a negative value.
    
    if(power_difference > max)
        power_difference = max;
    if(power_difference < -max)
        power_difference = -max;

    if(power_difference < 0)
      go(max+power_difference, max);
    else
        go(max, max-power_difference);
       }
    }
         

    void go(int speedLeft, int speedRight) {

      if (speedLeft > 0) {
  motor1.setSpeed(speedLeft); 
  motor1.run(FORWARD); 
        

      }

      else {

       motor1.setSpeed(-speedLeft); 

motor1.run(BACKWARD); 


      }



      if (speedRight > 0) {

          motor2.setSpeed(speedRight); 
  motor2.run(FORWARD); 
      }

      else {

          motor2.setSpeed(-speedRight); 
  motor2.run(BACKWARD); 
      }

    }

    
