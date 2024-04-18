const int trigPin = 2;//ultrasonic sensor's trigger
const int echoPin = 3;//ultrasonic sensor's echo
const int irPinLeft = 4; // Left infrared sensor output pin
const int irPinRight = 5; // Right infrared sensor output pin
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

  irLeftDetected = digitalRead(irPinLeft);
  irRightDetected = digitalRead(irPinRight);

  if(irLeftDetected == LOW && irRightDetected == HIGH) {
    Serial.println("Veering left");
  } else if(irLeftDetected == HIGH && irRightDetected == LOW) {
    Serial.println("Veering right");
  } else if(irLeftDetected == LOW && irRightDetected == LOW) {
    Serial.println("On track");
  } else {
    Serial.println("Lane departure or no detection");
  }
  delay(500);
}
