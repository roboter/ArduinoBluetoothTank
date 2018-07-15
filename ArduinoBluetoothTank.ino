// Define Motor Driver Pins
int ENA = 9;
int IN1 = 7;
int IN2 = 8;

int IN3 = 2;
int IN4 = 4;
int ENB = 10;


// Define Motor Speed Value
int motorSpeed = 80; // Normal Speed
int motorTurnSpeed = 110; // Speed When Turning Left or Right

char val; // Define val To Store The Serial Input


void setup() // Run once, when the sketch starts
{
  Serial.begin(9600); // Set the baud rate to match with bluetooth
  pinMode(ENA, OUTPUT); // Sets the pin as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}


void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed); // Enable Motor & Set the Speed

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);
}


void backward()
{
  digitalWrite(IN1, LOW); // Motor drivers may have difference setting, change it accordingly
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorSpeed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, motorSpeed);
}


void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorTurnSpeed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorTurnSpeed);
}


void right()
{
  analogWrite(ENA, motorTurnSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, motorTurnSpeed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void motorStop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


void loop() // Run continuously until powered down
{
  val = Serial.read(); // Read & store information from the serial port to val

  if (val != -1) {

    if (val == 'w' || val == '8')
      forward();

    else if (val == 'x' || val == '2')
      backward();

    else if (val == 'a' || val == '4')
      left();

    else if (val == 'd' || val == '6')
      right();

    else if (val == 's') motorStop();
  }
}
