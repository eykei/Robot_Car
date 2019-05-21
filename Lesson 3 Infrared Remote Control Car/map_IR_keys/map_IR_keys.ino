//Set the receiving pin, and run. Press a button on your remote to see its decimal value on the serial printout. note pressing and holding a button will transmit the code once, then max value (FFFFFF in hex)

#include <IRremote.h>

const int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value);
        irrecv.resume();
  }
}

