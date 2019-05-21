// 

#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = A4;
int Trig = A5;

#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6
#define carSpeed 200

int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void halt() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

//Ultrasonic distance measurement
int getDistance() {
    //set trig pin to low for 2 microsec to clear it
    digitalWrite(Trig, LOW); 
    delayMicroseconds(2);

    //emit ultrasound for 10 microsec
    digitalWrite(Trig, HIGH); 
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);

    //measure the time (in microsec) that echo reads high. this is the time between when the wave was sent vs received. 
    int echoTime = pulseIn(Echo, HIGH);

    int distance = echoTime * 0.017; // 0.017 = 0.034 /2... 340 m/s (speed of sound) - > 0.034 cm / microsec and divide by 2 to account for 2 way travel
    
    return distance; // returns distance in centimeters    
}

void setup() {
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  halt();
}

void loop() {
    myservo.write(90);  //set servo position - sensor facing forward
    delay(500);
    middleDistance = getDistance(); //obtain distance of objects in front

    if(middleDistance <= 20) { //if object in front is near, stop, then "look" to the right, then left
      halt();
      delay(500);
      myservo.write(0);
      delay(1000);
      rightDistance = getDistance();
      delay(1000);
      myservo.write(180);
      delay(1000);
      leftDistance = getDistance();

      delay(500);
      myservo.write(90);
      delay(1000);

      if ((rightDistance >= 20) || (leftDistance >= 20)){ //if either left or right distance is larger than 20 cm
        if(rightDistance > leftDistance) { //if the object to the right is farther, turn right for 360 ms 
          right();
          delay(300);
        }
        else if(rightDistance <= leftDistance) { //if the object to the left is farther, turn left
          left();
          delay(300);
        }
      }
      else { //if there are objects on both sides (and in front), go backward for 180 ms
        back();
        delay(600);
      }
    }
    else {
        forward(); //if no object is near the front, continue forward
    }
}
