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
  Serial3.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(SMOKE_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
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

  int fanState = 0;
  if (!isnan(temperature)) {
    if (temperature >= tempThreshold) {
      digitalWrite(RELAY_PIN, LOW);
      fanState = 1;
    } else {
      digitalWrite(RELAY_PIN, HIGH);
    }
  }

  int smokeState = digitalRead(SMOKE_PIN) == LOW ? 1 : 0;
  int buzzerState = smokeState;
  int ledState = digitalRead(IR2_PIN) == HIGH ? 1 : 0;

  if (smokeState)
    tone(BUZZER_PIN, 1000);
  else
    noTone(BUZZER_PIN);

  digitalWrite(LED_PIN, ledState);

  Serial3.print("T:");
  Serial3.print(temperature);
  Serial3.print(",F:");
  Serial3.print(fanState);
  Serial3.print(",D:");
  Serial3.print(doorOpened);
  Serial3.print(",S:");
  Serial3.print(smokeState);
  Serial3.print(",B:");
  Serial3.print(buzzerState);
  Serial3.print(",L:");
  Serial3.println(ledState);

  delay(2000);
}
