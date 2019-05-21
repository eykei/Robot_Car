// An array of 3 IR lights and 3 corresponding sensors lined up abreast can track a line on the floor. 
// If an IR sensor picks up low light (aka dark region, the line of black tape) it outputs low.
// If an IR sensor picks up high light (aka light region, a surface that is reflecting more light than black tape) it outputs high
// The potentiometer on the line tracking module can adjust the threshold

//Line Tracking IO define
#define IR_R !digitalRead(10)
#define IR_M !digitalRead(4) //IR_M is HIGH when sensor output is LOW (when line is detected)
#define IR_L !digitalRead(2)

#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6

#define carSpeed 150

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("forward");
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Serial.println("backward");
}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("left");
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  //Serial.println("right");
} 

void halt(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   //Serial.println("stop");
} 

void setup(){
  Serial.begin(9600);
}

void loop() {
  Serial.print("Left IR: ");
  Serial.print(IR_L);
  Serial.print("  Middle IR: ");
  Serial.print(IR_M);
  Serial.print("  Right IR: ");
  Serial.print(IR_R);
  Serial.println();
  if(IR_M){ //if middle IR detects line, go forward
    forward();
  }
  else if(IR_R) { //if right IR detects line, turn right
    while (IR_R){
      right();
    }
  }
  else if(IR_L) { //if left IR detects line, turn left
    while (IR_L){
      left();
    }
  }
  else {
    while (!IR_L && !IR_R){ //if no line is detected, end of line was reached. Turn around until either left or right sensors detect line
      right();
    }
  }
  delay(20);
}

