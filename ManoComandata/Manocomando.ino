/*
 MouseGlove - Device program
 Author: Ivan Gualandri
 */
 
 #include <TinkerKit.h>

TKAccelerometer accelerometer(I0, I1);  // creating the object 'accelerometer' that belongs to the 'TKAccelerometer' class 
                       	      		// and giving the values to the desired input pins
TKLed xLed(O1), yLed(O0);     		// creating the objects 'xLed' & 'yLed' that both belongs to the 'TKLed' class 
                              		// and giving the values to the desired output pins

int xAxisValue = 0;           // value read from the accelerometer's x-axis 
int yAxisValue = 0;           // value read from the accelerometer's y-axis
//char inData[20]; // Allocate some space for the string
//int zero_G = 512;
//float scale = 102.3; 

const int analogInPin1 = I0;  // Analog input pin that the Accelerometer's first pin is attached to
const int analogInPin2 = I1;  // Analog input pin that the Accelerometer's second pin is attached to
const int activation_button = 7;
const int motorPort = 9;
const int leftPort = 2;
const int rightPort = 3;
const int upPort = 4;
const int downPort = 5;

const int led_port=13;
int xRest = 0;
int yRest = 0;
int val = 0;
const int xdelta = 15;
const int ydelta = 30;

void setup()
{
  // start serial port at 57600 bps:
  pinMode(activation_button, INPUT);    
  Serial.begin(57600);
//  Serial.println("Startingup..."); 
//  Serial.println("Stay still for 2 seconds...");
  xRest = avgValueX();
  yRest = avgValueY();
  delay(2000);
  pinMode(motorPort, OUTPUT);
  pinMode(leftPort, OUTPUT);
  pinMode(rightPort, OUTPUT);
  pinMode(upPort, OUTPUT);
  pinMode(downPort, OUTPUT);
  
  digitalWrite(led_port, HIGH);
  Serial.println(xRest);
    Serial.println(yRest);
                 digitalWrite(upPort, LOW);
      digitalWrite(downPort, LOW);
            digitalWrite(rightPort, LOW);
      digitalWrite(leftPort, LOW); 
}

void loop() 
{
//  xAxisValue = accelerometer.getXAxis();  
//  yAxisValue = accelerometer.getYAxis(); 
int val = digitalRead(activation_button);
if(val==HIGH) {
    xAxisValue = avgValueX() - xRest;
    yAxisValue = avgValueY() - yRest;
  //  xAxisValue = analogRead(analogInPin1);  
  //  yAxisValue = analogRead(analogInPin2);  
  //  xNor = ((float)xAxisValue - (float)zero_G)/scale;
  //  int outputValue1 = map(xAxisValue, 0, 1023, 0, 255);  
  //  int outputValue2 = map(xAxisValue, 0, 1023, 0, 255); 
    
    Serial.print("Y=" );                       
    Serial.print(xAxisValue);   
    Serial.print("X=" );                       
    Serial.println(yAxisValue);
    if(abs(yAxisValue) >  xdelta){
      if(yAxisValue > 0) {
        digitalWrite(rightPort, LOW);
        digitalWrite(leftPort, HIGH);
        Serial.println("LEFT");
      } else if(yAxisValue < 0){
        digitalWrite(rightPort, HIGH);
        digitalWrite(leftPort, LOW);
        Serial.println("RIGHT");
      } 
     } else {
        digitalWrite(rightPort, LOW);
        digitalWrite(leftPort, LOW);      
        Serial.println("XREST");
     }

    
    if(abs(xAxisValue)>ydelta){
      if(xAxisValue > 0){
        digitalWrite(upPort, LOW);
        digitalWrite(downPort, HIGH);
//        digitalWrite(motorPort, HIGH);
        Serial.println("DOWN");
      } else if(xAxisValue< 0){
        digitalWrite(upPort, HIGH);
        digitalWrite(downPort, LOW);
//        digitalWrite(motorPort, HIGH);
        Serial.print("UP");
      }
    } else {
        digitalWrite(upPort, LOW);
        digitalWrite(downPort, LOW); 
//        digitalWrite(motorPort, LOW);
        Serial.println("YREST");
    }
    
}

else {
//       digitalWrite(motorPort, LOW);
             digitalWrite(upPort, LOW);
      digitalWrite(downPort, LOW);
            digitalWrite(rightPort, LOW);
      digitalWrite(leftPort, LOW); 
}  
 /*    while(Serial.available() > 0) {
      char incomingByte = Serial.read();
      
      digitalWrite(motorPort, HIGH);
      delay(20);
    }*/
/*    digitalWrite(motorPort, LOW);
} else {
  delay(20);
  digitalWrite(motorPort, LOW);
}*/
/*  
  // set the leds brightnes
  // print the results to the serial monitor:
  Serial.print("X=" );                       
  Serial.print(xNor);   
  Serial.print("Y=" );                       
  Serial.println(yNor);     
*/
}

int avgValueX(){
 int readX=0; 
 int i=0;
 while(i<10) {
   readX += accelerometer.getXAxis();  
   i++;
 }
 return readX/10;
}

int avgValueY(){
 int readY=0; 
 int i=0;
 while(i<10) {
   readY += accelerometer.getYAxis();  
   i++;
 }
 return readY/10;
}
