/*
  KeyboardLCD library
 
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */


// include the library code:
#include <LiquidCrystal.h>
#include <PS2Keyboard.h>

#define DATA_PIN 7
#define IRQ_PIN 3

PS2Keyboard keyboard;
int counter;
int request_state;
char name[16];  


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 6, 2);

void setup() {
  keyboard.begin(DATA_PIN, IRQ_PIN, PS2Keymap_US);

//  Serial.begin(9600);
  delay(1000);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Your name? ");
  request_state =0;
  counter=0;
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):  
  if(counter==16){
    counter=0;
  }
  lcd.setCursor(counter, 1);
  // print the number of seconds since reset:
  //lcd.print(millis()/1000);
  if(keyboard.available()) {
    char dat = keyboard.read();
    byte val = dat - '0';
    if(request_state==0 && dat!=PS2_ENTER){
      name[counter]=dat;      
    }
    
    if(dat==PS2_ENTER){
      if(request_state==0) {
        request_state = 1;
        lcd.setCursor(0,0);
        lcd.print("Hello ");
        lcd.print(name);
        lcd.print("!!!!");
      } 
      lcd.setCursor(0,1);
      int i=0;
      while(i<16){
        lcd.print(' ');
        i++;
      }
      lcd.setCursor(0,1);
      counter=0;
    } else if(dat==PS2_DELETE){
      counter--;
      lcd.setCursor(counter,1);
      lcd.print(' ');
    } else if(dat >= 0) {
//      Serial.print(val, DEC);
      lcd.print(dat);
      counter++;
    }
  }
}

