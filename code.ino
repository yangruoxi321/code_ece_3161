const int trigPin = 2;  // ultrasonic sensor's trigger
const int echoPin = 3;  // ultrasonic sensor's echo
const int irPinLeft = 4;   // Left infrared sensor output pin
const int irPinRight = 5;  // Right infrared sensor output pin

// L298N Motor Driver pins
const int enA = 6;  // PWM pin for motor A
const int in1 = 7;  // Direction pin 1 for motor A
const int in2 = 8;  // Direction pin 2 for motor A
const int in3 = 9;  // Direction pin 1 for motor B
const int in4 = 10; // Direction pin 2 for motor B
const int enB = 11; // PWM pin for motor B

long duration;
float distance;
int irLeftDetected;
int irRightDetected;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPinLeft, INPUT);
  pinMode(irPinRight, INPUT);
  
  // Set L298N motor driver pins as output
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < 5) {
    // Stop the car if distance is less than 5 cm
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    Serial.println("Obstacle detected. Stopping the car.");
  } else {
    irLeftDetected = digitalRead(irPinLeft);
    irRightDetected = digitalRead(irPinRight);
    
    if (irLeftDetected == LOW && irRightDetected == HIGH) {
      Serial.println("Veering left");
      // Turn right
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enA, 200);
      analogWrite(enB, 200);
    } else if (irLeftDetected == HIGH && irRightDetected == LOW) {
      Serial.println("Veering right");
      // Turn left
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 200);
      analogWrite(enB, 200);
    } else if (irLeftDetected == LOW && irRightDetected == LOW) {
      Serial.println("On track");
      // Move forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 200);
      analogWrite(enB, 200);
    } else {
      Serial.println("Lane departure or no detection");
      // Stop
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
    }
  }
  
  delay(500);
}