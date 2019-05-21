//infrared controlled car has 5 buttons, forward, backward, left, right, and stop. Hold button to continue command

#include <IRremote.h>

//IR Remote Codes, specified in remote manual
#define FORWARD 16736925
#define BACK    16754775
#define LEFT    16720605
#define RIGHT   16761405
#define STOP    16712445

#define RECV_PIN  12

#define ENB 5   // Left  wheel speed
#define IN1 7   // Left  wheel forward
#define IN2 8   // Left  wheel reverse
#define IN3 9   // Right wheel reverse
#define IN4 11  // Right wheel forward
#define ENA 6   // Right wheel speed
#define carSpeed 200  // initial speed of car >=0 to <=255

IRrecv irrecv(RECV_PIN); //create an IRrecv object and specify signal pin
decode_results results; //create a decode_results object, a data type part of IRremote.h
unsigned long val;
unsigned long preMillis;

void forward() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void halt(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  halt();
  irrecv.enableIRIn();  //start the receiver
  irrecv.blink13(true); // blink on board LED when an IR signal is received
}

void loop() {
  if (irrecv.decode(&results)){  //returns true if signal is received
    preMillis = millis();
    val = results.value; //a decimal number, the IR Key Code
    Serial.println(val);
    irrecv.resume(); //reset receiver, prepare to receive next code (signal)
    switch(val){
      case FORWARD: forward();  break;
      case BACK:    back();     break;
      case LEFT:    left();     break;
      case RIGHT:   right();    break;
      case STOP:    halt();     break;
      default:                  break; 
      //if you hold down a button, after sending the initial code it will repeat max value FFFFFF code. 
      //by setting a default case of "nothing", the robot will continue the last command when it receives the repeat code
    }
  }
  else{
    if(millis() - preMillis > 200){ //if no command is received in a half second, stop
      halt();
      preMillis = millis();
    }
  }
}
