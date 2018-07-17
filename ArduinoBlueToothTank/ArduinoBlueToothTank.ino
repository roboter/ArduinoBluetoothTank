#include <../lib/advancedSerial/src/advancedSerial.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 1); // RX, TX
// Define Motor Driver Pins

int IN1 = 4;
int IN2 = 5;

int IN3 = 6;
int IN4 = 9;
int LED = 13;
int state = 0;
int motorSpeed = 150;   // Normal Speed
int motorTurnSpeed = 0; // Speed When Turning Left or Right
int delayMs = 15000;
void setup() {
  mySerial.begin(9600); // set up Serial library at 9600 bps
  Serial.begin(9600);
  aSerial.setPrinter(Serial);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED, OUTPUT);
}
void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  delay(100);
}
void loop() { // if some data is sent, read it and save it in the state variable

  // if (Serial.available() > 0)
  if (mySerial.available() > 0) {
    // state = Serial.read();
    state = mySerial.read();
    Serial.println(state);
    delay(10);
    if (state == 0x31) // If 1 Forwards
    {
      digitalWrite(LED, HIGH);
      analogWrite(IN1, motorSpeed);
      analogWrite(IN3, motorSpeed);
      digitalWrite(IN4, LOW);

      Serial.println("forward");
      delay(100);
      stop();
      digitalWrite(LED, LOW);

    } else if (state == '2') // If 2 Turn Left
    {
      digitalWrite(IN1, LOW);
      analogWrite(IN2, motorSpeed);
      analogWrite(IN3, motorSpeed);

      digitalWrite(IN4, LOW);

      delay(100);
      stop();
    } else if (state == '3') { // If 3 Turn Right

      analogWrite(IN1, motorSpeed);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      analogWrite(IN4, motorSpeed);
      delay(100);
      stop();
    } else if (state == '4') // If 4 Backwards
    {
      digitalWrite(IN1, LOW); // Motor drivers may have difference setting,
                              // change it accordingly
      analogWrite(IN2, motorSpeed);
      digitalWrite(IN3, LOW);
      analogWrite(IN4, motorSpeed);

      delay(100);
      stop();
    }

    else if (state >= '9') {

      delay(100);
      state = 0;
    }
  }
}
