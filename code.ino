const int trigPin = 2;
const int echoPin = 3;
const int irPinLeft = 4; // 左侧红外传感器输出引脚
const int irPinRight = 5; // 右侧红外传感器输出引脚
long duration;
float distance;
int irLeftDetected;
int irRightDetected;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPinLeft, INPUT); // 设置左侧IR传感器引脚为输入
  pinMode(irPinRight, INPUT); // 设置右侧IR传感器引脚为输入
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
