#include <../lib/advancedSerial/src/advancedSerial.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(/*RX*/ 2, /*TX*/ 1);
// Define Motor Driver Pins

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 9;

int LED = 13;

// int state = 0;
int motorSpeed = 150; // Normal Speed
// int motorTurnSpeed = 0; // Speed When Turning Left or Right
// int delayMs = 15000;
/*
  Front Motor (Steering) => Channel A
  Back Motor => Channel B

  Since the motor shield hijacks 6 pins for the motors'
  control, they are declared in the MotorShieldR3 library.
*/

//#define pinfrontLights 7 // Pin that activates the Front lights.
//#define pinbackLights 4  // Pin that activates the Back lights.
char command = 'S';
char prevCommand = 'A';
int velocity = 0;
unsigned long timer0 =
    2000; // Stores the time (in millis since execution started)
unsigned long timer1 =
    0; // Stores the time when the last command was received from the phone

void setup() {
  mySerial.begin(9600); // set up Serial library at 9600 bps
  Serial.begin(9600);
  aSerial.setPrinter(Serial);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("connected");
  aSerial.println("aserial");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    timer1 = millis();
    prevCommand = command;
    command = Serial.read();
    // Change pin mode only if new command is different from previous.
    if (command != prevCommand) {
      // Serial.println(command);
      aSerial.print("command = ")
          .print(command)
          .print("speed=")
          .println(velocity);
      switch (command) {
      case 'F':
        // yellowCar.Forward_4W(velocity);
        break;
      case 'B':
        // yellowCar.Back_4W(velocity);
        break;
      case 'L':
        // yellowCar.Left_4W();
        break;
      case 'R':
        // yellowCar.Right_4W();
        break;
      case 'S':
        // yellowCar.Stopped_4W();
        break;
      case 'I': // FR
        // yellowCar.ForwardRight_4W(velocity);
        break;
      case 'J': // BR
        // yellowCar.BackRight_4W(velocity);
        break;
      case 'G': // FL
        // yellowCar.ForwardLeft_4W(velocity);
        break;
      case 'H': // BL
        // yellowCar.BackLeft_4W(velocity);
        break;
      case 'W': // Font ON
        // digitalWrite(pinfrontLights, HIGH);
        break;
      case 'w': // Font OFF
        // digitalWrite(pinfrontLights, LOW);
        break;
      case 'U': // Back ON
        // digitalWrite(pinbackLights, HIGH);
        break;
      case 'u': // Back OFF
        // digitalWrite(pinbackLights, LOW);
        break;
      case 'D': // Everything OFF
        // digitalWrite(pinfrontLights, LOW);
        // digitalWrite(pinbackLights, LOW);
        // yellowCar.Stopped_4W();
        break;
      default: // Get velocity
        if (command == 'q') {
          velocity = 255; // Full velocity
          // yellowCar.SetSpeed_4W(velocity);
        } else {
          // Chars '0' - '9' have an integer equivalence of 48 - 57,
          // accordingly.
          if ((command >= 48) && (command <= 57)) {
            // Subtracting 48 changes the range from 48-57 to 0-9.
            // Multiplying by 25 changes the range from 0-9 to 0-225.
            velocity = (command - 48) * 25;
            // yellowCar.SetSpeed_4W(velocity);
          }
        }
      }
    }
  } else {
    timer0 = millis(); // Get the current time (millis since execution started).
    // Check if it has been 500ms since we received last command.
    if ((timer0 - timer1) > 500) {
      // More tan 500ms have passed since last command received, car is out of
      // range. Therefore stop the car and turn lights off.
      // digitalWrite(pinfrontLights, LOW);
      // digitalWrite(pinbackLights, LOW);
      Stop();
      // yellowCar.Stopped_4W();
    }
  }
}

void Forward() {
  digitalWrite(LED, HIGH);
  analogWrite(IN1, motorSpeed);
  analogWrite(IN3, motorSpeed);
  digitalWrite(IN4, LOW);
}

void Back() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, motorSpeed);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, motorSpeed);
}
void Left() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, motorSpeed);
  analogWrite(IN3, motorSpeed);
  digitalWrite(IN4, LOW);
}

void Right() {
  analogWrite(IN1, motorSpeed);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, motorSpeed);
}
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
