// Final SumoBot code, calibrated to work when suppling 18 V to DC motors
// Author: Richard Salas Chavez

#include <Timer.h>
#define trigPin 0
#define echoPin 2

//motor1
int InA1 = 7;
int InB1 = 8;
int En1 = 6;

//motor2
int InA2 = 12;
int InB2 = 13;
int En2 = 11;

//line sensor
int left_line;
int right_line;

//SONAR sensor
unsigned long duration;
unsigned long distance;

//variable to keep track of time... miliseconds
unsigned long previousTime = 0;
unsigned long currentTime = 0;

Timer t;

void read_sensors();

void setup()
{
  Serial.begin(9600);

  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(En1, OUTPUT);

  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);
  pinMode(En2, OUTPUT);

  //SONAR sensor
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);

  t.every(100, read_sensors);
}

void loop() {
  // 3 second delay as required by competition
  if (currentTime >= 3000)
  {
    // counter is introduced to perform a star and stop motion at the start
    // to ensure that hinged ramp falls over and does not cover the ultrasonic
    // sensor
    // counter ensures that this action is performed only once
    if (count == 0)
    {
      previousTime = currentTime;
      while (currentTime - previousTime <= 150)
      {
        if (currentTime - previousTime <= 75)
          straight();
        else 
          straightBack();
        currentTime = millis();
      }
      count ++;
    }

  else
  {
    currentTime = millis();
  }
}

void next()
{
  if (distance <= 25) // if the ultrasonic sensor detects something nearby (25 cm)
  {
    straight();     // then push it
  }

  else if (left_line + right_line > 0) // if either or both line sensors are activated
  {
    while (currentTime - previousTime <= 2000)
    {
      if (currentTime - previousTime <= 1300)
        straightBack();  // go straight back for some time
      else
        spin();         // spin around to recover
      currentTime = millis();
    }
  }

  else // spin in a circle until it finds oponent or line sensors are activated
  {
    long num = (currentTime % 3000);
    if (num == 0)
      spin();
    else
      straight();
  }
}

void read_sensors()
{
  left_line = analogRead(A5); // left line sensor
  right_line = analogRead(A4); // right line sensor

  // ultrasonic sensor
  digitalWrite(trigPin,LOW);
  delayMicroseconds (2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = duration/58.2; // divide by 58.2 gives distance in cm

  next();
}

void straight(){
  digitalWrite(En1, HIGH);
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);

  digitalWrite(En2, HIGH);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
}

void straightBack(){
  digitalWrite(En1, HIGH);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);

  digitalWrite(En2, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}

void turnBack_left(){
  digitalWrite(En1, HIGH);
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);

  digitalWrite(En2, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}

void turnBack_right(){
  digitalWrite(En1, HIGH);
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);

  digitalWrite(En2, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}

void spin()
{
  digitalWrite(En1, 150);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);

  digitalWrite(En2, 150);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
}
