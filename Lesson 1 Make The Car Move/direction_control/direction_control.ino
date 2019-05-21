// Demonstration: Go forward for 1 sec, go backward for 1 sec, turn left for one sec, turn right for one sec (repeat)

// ENA and ENB provide power to the motors (and can control speed via pwm)
// IN1 and IN2 pins govern the two left wheels. IN3 and IN4 pins govern the two right wheels  
//  ENA   ENB   IN1   IN2   IN3   IN4   
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car moves forward (All wheels forward)
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car moves back (All wheels backward)
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car turns left (Left wheels backward, Right wheels forward.)
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car turns right (Right wheels backward, Left wheels forward.)
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car doesn't move
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car doesn't move
//  LOW   LOW   N/A   N/A   N/A   N/A   Car doesn't move


//define L298n Pinout
#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6

void forward(){
  digitalWrite(ENA, HIGH);    //enable L298n A channel
  digitalWrite(ENB, HIGH);    //enable L298n B channel
  digitalWrite(IN1, HIGH);    //set IN1 hight level
  digitalWrite(IN2, LOW);     //set IN2 low level
  digitalWrite(IN3, LOW);     //set IN3 low level
  digitalWrite(IN4, HIGH);    //set IN4 hight level
  Serial.println("Forward");  //send message to serial monitor
}

void back(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

void left(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}

void right(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}


void setup() {
  Serial.begin(9600);     //open serial and set the baudrate
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}


void loop() {
  forward();    //go forward
  delay(1000);  //delay 1000 ms
  back();       //go back
  delay(1000);
  left();       //turning left
  delay(1000);
  right();      //turning right
  delay(1000);
}
