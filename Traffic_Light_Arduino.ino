const int redPin1 = 9;
const int yellowPin1 = 10;
const int greenPin1 = 11;
const int redPin2 = 3;
const int yellowPin2 = 4;
const int greenPin2 = 5;

const int buttonPin = 2;
const int buttonPin2 = 6;
const int buzzerPin = 8;

const unsigned long greenDuration = 5000;
const unsigned long yellowDuration = 2000;

int buttonState = 0;
int lastButtonState = 0;
bool pedestrianRequested = false;

int buttonState2 = 0;
int lastButtonState2 = 0;
bool pedestrianRequested2 = false;

unsigned long previousMillis = 0;
int currentState = 0;

void setup() {
  pinMode(redPin1, OUTPUT);
  pinMode(yellowPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(yellowPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);

  Serial.begin(9600);

  digitalWrite(redPin1, HIGH);
  digitalWrite(yellowPin1, LOW);
  digitalWrite(greenPin1, LOW);
  digitalWrite(redPin2, LOW);
  digitalWrite(yellowPin2, LOW);
  digitalWrite(greenPin2, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    delay(50);
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH && lastButtonState == LOW) {
      Serial.println("Button 1 Pressed");
      if (currentState == 0) {
        digitalWrite(redPin2, LOW);
        digitalWrite(yellowPin2, HIGH);
        digitalWrite(greenPin2, LOW);
        currentState = 1;
        previousMillis = currentMillis;
        pedestrianRequested = true;
      } else if (currentState == 2) {
        digitalWrite(redPin1, LOW);
        digitalWrite(yellowPin1, HIGH);
        digitalWrite(greenPin1, LOW);
        currentState = 3;
        previousMillis = currentMillis;
        pedestrianRequested = true;
      } else {
        pedestrianRequested = true;
      }
    }
    lastButtonState = buttonState;
  }

  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 != lastButtonState2) {
    delay(50);
    buttonState2 = digitalRead(buttonPin2);
    if (buttonState2 == HIGH && lastButtonState2 == LOW) {
      Serial.println("Button 2 Pressed");
      if (currentState == 0) {
        digitalWrite(redPin2, LOW);
        digitalWrite(yellowPin2, HIGH);
        digitalWrite(greenPin2, LOW);
        currentState = 1;
        previousMillis = currentMillis;
        pedestrianRequested2 = true;
      } else if (currentState == 2) {
        digitalWrite(redPin1, LOW);
        digitalWrite(yellowPin1, HIGH);
        digitalWrite(greenPin1, LOW);
        currentState = 3;
        previousMillis = currentMillis;
        pedestrianRequested2 = true;
      } else {
        pedestrianRequested2 = true;
      }
    }
    lastButtonState2 = buttonState2;
  }

  switch (currentState) {
    case 0:
      if (currentMillis - previousMillis >= greenDuration) {
        digitalWrite(redPin2, LOW);
        digitalWrite(yellowPin2, HIGH);
        digitalWrite(greenPin2, LOW);
        currentState = 1;
        previousMillis = currentMillis;
      }
      break;

    case 1:
      if (currentMillis - previousMillis >= yellowDuration) {
        digitalWrite(redPin2, HIGH);
        digitalWrite(yellowPin2, LOW);
        digitalWrite(greenPin2, LOW);
        delay(1000);
        digitalWrite(redPin1, LOW);
        digitalWrite(yellowPin1, LOW);
        digitalWrite(greenPin1, HIGH);


        if (pedestrianRequested) {
          pedestrianPhase(1);
          pedestrianRequested = false;
        }
        if (pedestrianRequested2) {
          pedestrianPhase(2);
          pedestrianRequested2 = false;
        }

        currentState = 2;
        previousMillis = currentMillis;
      }
      break;

    case 2:
      if (currentMillis - previousMillis >= greenDuration) {
        digitalWrite(redPin1, LOW);
        digitalWrite(yellowPin1, HIGH);
        digitalWrite(greenPin1, LOW);
        currentState = 3;
        previousMillis = currentMillis;
      }
      break;

    case 3:
      if (currentMillis - previousMillis >= yellowDuration) {
        digitalWrite(redPin1, HIGH);
        digitalWrite(yellowPin1, LOW);
        digitalWrite(greenPin1, LOW);
        delay(1000);
        digitalWrite(redPin2, LOW);
        digitalWrite(yellowPin2, LOW);
        digitalWrite(greenPin2, HIGH);

        if (pedestrianRequested) {
          pedestrianPhase(1);
          pedestrianRequested = false;
        }
        if (pedestrianRequested2) {
          pedestrianPhase(2);
          pedestrianRequested2 = false;
        }

        currentState = 0;
        previousMillis = currentMillis;
      }
      break;
  }
}

void pedestrianPhase(int side) {
  digitalWrite(redPin1, HIGH);
  digitalWrite(yellowPin1, LOW);
  digitalWrite(greenPin1, LOW);
  digitalWrite(redPin2, HIGH);
  digitalWrite(yellowPin2, LOW);
  digitalWrite(greenPin2, LOW);
  delay(500);

  if (side == 1) {
    digitalWrite(redPin1, LOW);
    digitalWrite(greenPin1, HIGH);
  } else if (side == 2) {
    digitalWrite(redPin2, LOW);
    digitalWrite(greenPin2, HIGH);
  }

  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 1000);
    delay(1000);
    noTone(buzzerPin);
    delay(1000);
  }

  if (side == 1) {
    digitalWrite(greenPin1, LOW);
    digitalWrite(redPin1, HIGH);
  } else if (side == 2) {
    digitalWrite(greenPin2, LOW);
    digitalWrite(redPin2, HIGH);
  }
}
