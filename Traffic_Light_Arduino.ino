const int redPin = 9;
const int yellowPin = 10;
const int greenPin = 11;
const int buttonPin = 2;
const int buzzerPin = 8;

const unsigned long redDuration = 5000;
const unsigned long greenDuration = 5000;
const unsigned long yellowDuration = 2000;

int buttonState = 0;
int lastButtonState = 0;
bool pedestrianRequested = false;
unsigned long previousMillis = 0;
int currentState = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    delay(50);
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH && lastButtonState == LOW) {
      Serial.println("Button Pressed");
      if (currentState == 1) {
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(greenPin, LOW);
        currentState = 2;
        previousMillis = millis();
        pedestrianRequested = true;
      } else if (currentState == 0 || currentState == 2) {
        pedestrianRequested = true;
      }
    } else if (buttonState == LOW && lastButtonState == HIGH) {
      Serial.println("Button Not Pressed");
    }
  }
  lastButtonState = buttonState;

  unsigned long currentMillis = millis();

  switch (currentState) {
    case 0:
      if (currentMillis - previousMillis >= redDuration) {
        if (pedestrianRequested) {
          pedestrianPhase();
          pedestrianRequested = false;
        }
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, HIGH);
        currentState = 1;
        previousMillis = currentMillis;
      }
      break;

    case 1:
      if (currentMillis - previousMillis >= greenDuration) {
        if (pedestrianRequested) {
          digitalWrite(redPin, LOW);
          digitalWrite(yellowPin, HIGH);
          digitalWrite(greenPin, LOW);
          currentState = 2;
          previousMillis = currentMillis;
        } else {
          digitalWrite(redPin, LOW);
          digitalWrite(yellowPin, HIGH);
          digitalWrite(greenPin, LOW);
          currentState = 2;
          previousMillis = currentMillis;
        }
      }
      break;

    case 2:
      if (currentMillis - previousMillis >= yellowDuration) {
        digitalWrite(redPin, HIGH);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, LOW);
        currentState = 0;
        previousMillis = currentMillis;
        if (pedestrianRequested) {
          pedestrianPhase();
          pedestrianRequested = false;
        }
      }
      break;
  }
}

void pedestrianPhase() {
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);

  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 1000);
    delay(1000);
    noTone(buzzerPin);
    delay(1000);
  }
}
