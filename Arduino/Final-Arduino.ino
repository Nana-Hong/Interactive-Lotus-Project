const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; 
int ledPin = 13;
int greenLedPin = 12;
int redLedPin = 11;
int sensorPin = 0;
int sensorValue = 0;
int sensorValue2 = 0;


void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  pinMode (ledPin, OUTPUT);
}

void loop()
{
   long duration, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   sensorValue2 = cm;
   
  sensorValue = analogRead(sensorPin);
  char inByte = 0;
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    cm = Serial.read();

    if (inByte == 'a') {
      digitalWrite(greenLedPin, HIGH);
      delay(500);
      digitalWrite(greenLedPin, LOW);
    }

    if (inByte == 'b') {   
        digitalWrite(redLedPin, HIGH);
        delay(500);
        digitalWrite(redLedPin, LOW);
    }

    if (inByte == 'c') {
      for (int i = 0; i < 4; i++) {
        digitalWrite(ledPin, HIGH);
        delay(sensorValue+50);
        digitalWrite(ledPin, LOW);
        delay(sensorValue+50);
      }
    }
  }
   Serial.write(sensorValue);

   Serial.write(sensorValue2);
}


long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
