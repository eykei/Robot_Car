// From max speed forward, decelerate to rest, wait one second, accelerate to max speed backward, wait two seconds, repeat

#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  //set to go forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  //decelerate from max speed
  for(int i = 255; i >= 0; i--){
    analogWrite(ENB, i);
    analogWrite(ENA, i);
    delay(20);
  }

  //stop for one second
  analogWrite(ENB, 0); //same as digitalWrite low
  analogWrite(ENA, 0);
  delay(1000);

  //set to go backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  //accelerate from rest
  for(int i = 0; i <= 255; i++){
    analogWrite(ENB, i);
    analogWrite(ENA, i);
    delay(20);
  }
  
  //stop for two seconds
  digitalWrite(ENB, LOW); 
  digitalWrite(ENA, LOW);
  delay(2000);
}
