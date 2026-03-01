#include <DHT.h>
#include <Servo.h>

#define DHT_PIN 7
#define DHT_TYPE DHT11
#define RELAY_PIN 30
#define IR_PIN 8
#define SERVO_PIN 9
#define SMOKE_PIN 10
#define BUZZER_PIN 11
#define IR2_PIN 12
#define LED_PIN 13

DHT dht(DHT_PIN, DHT_TYPE);
Servo doorServo;

float tempThreshold = 20.0;
bool doorOpened = false;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(SMOKE_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);

  dht.begin();
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);
}

void loop() {

  if (digitalRead(IR_PIN) == LOW && !doorOpened) {
    doorServo.write(180);
    doorOpened = true;
  }

  float temperature = dht.readTemperature();

  if (!isnan(temperature)) {
    if (temperature >= tempThreshold)
      digitalWrite(RELAY_PIN, LOW);
    else
      digitalWrite(RELAY_PIN, HIGH);
  }

  if (digitalRead(SMOKE_PIN) == LOW)
    tone(BUZZER_PIN, 1000);
  else
    noTone(BUZZER_PIN);

  if (digitalRead(IR2_PIN) == HIGH)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);

  delay(200);
}
