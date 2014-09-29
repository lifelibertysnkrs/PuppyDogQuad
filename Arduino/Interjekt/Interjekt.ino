//Reads PPM signals from up to 6 channels of a reciever, allows for modification based on sensor input and transmitts it to a flight controller. 
//Tested on Spektrum DX5e with AR6100 Reciever, Arduino Uno, And Multiwii Pro Flight Controller. Should work on any combination, however. 


//Developed by Rahul Tiwari. Credits to eswink for the RC Input code.


#include <Servo.h>
Servo Throttle, Aile, Elev, Rudd, Aux1, Aux2;
extern int x[2];
//Create variables for 6 channels
int RXCH[6]; 
volatile int RXSG[6];
int RXOK[6];
int PWMSG[6];
int TXCH[6];

void setup() {
  
  //Start communication to serial port
  Serial.begin(9600);  
  
  //Assign PPM input pins:
  RXCH[0] = 2; //Throttle
  RXCH[1] = 4; //Aile / Yaw
  RXCH[2] = 7; //Elev. / Pitch
  RXCH[3] = 8;  //Rudd. / Roll
  RXCH[4] = 12;  //Aux1
  RXCH[5] = 13;  //Aux2
  
  //Assign PWM Transmitter pins (must have '~' symbol on pin to use):
  
  TXCH[0] = 3; //Throttle
  TXCH[1] = 5; //Aile / Yaw
  TXCH[2] = 6; //Elev. / Pitch
  TXCH[3] = 9;  //Rudd. / Roll
  TXCH[4] = 10;  //Aux1
  TXCH[5] = 11; //Aux2
  
  //Attach pins to correct variable
  Throttle.attach(TXCH[0]);
  Aile.attach(TXCH[1]);
  Elev.attach(TXCH[2]);
  Rudd.attach(TXCH[3]);
  Aux1.attach(TXCH[4]);
  Aux2.attach(TXCH[5]);
 
  //Variables for Image Tracking
  
  
  
  
  //Variables for R/C Channels
  for (int i = 0; i < 5; i++){
    pinMode(RXCH[i], INPUT);
  }
}

void loop() {
  
// Read RX values 
  for (int i = 0; i < 5; i++){                                        //for each of the 6 channels: 
  RXSG[i] = pulseIn(RXCH[i], HIGH, 20000);                            //read the receiver signal
  if (RXSG[i] == 0) {RXSG[i] = RXOK[i];} else {RXOK[i] = RXSG[i];}    //if the signal is good then use it, else use the previous signal
  PWMSG[i] = map(RXSG[i], 1000, 2000, 1000, 2000);                        //substitute the high values to a value between 0 and 511
  constrain (PWMSG[i], 1000, 2000);        //make sure that the value stays within the disired boundries
  
//************************Insert Modifying Code here************************//
//
//Image Tracking (from Rasberry Pi)
  PWMSG[0] = 1500; 
    
  if(PWMSG[4]>1600){
    PWMSG[0] += (x[0]);
    PWMSG[1] += (x[1]);
    }
  
    


//
//
//*************************************************************************//

  
 // Send RX Values to Flight Controller

  Throttle.writeMicroseconds(PWMSG[0]);
  Aile.writeMicroseconds(PWMSG[1]); 
  Elev.writeMicroseconds(PWMSG[2]);
  Rudd.writeMicroseconds(PWMSG[3]);
  Aux1.writeMicroseconds(PWMSG[4]);

 }
 Serial.println();
}
