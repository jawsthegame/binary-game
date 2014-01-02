const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int led4 = 10;

const int buzz = 9;

const int guessButton = 2;
const int completeButton = 3;

const int numLeds = 4;
int leds[] = {led1, led2, led3, led4};

const int winNum = 3;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(guessButton, INPUT);
  pinMode(completeButton, INPUT);
  pinMode(buzz, OUTPUT);
}

int inARow = 0;

void loop() {
  lights(LOW);

  int buttonState, complete;
  randomSeed(analogRead(0));

  int dec = random(0, 16);
  int orig = dec;
  if (dec == 0) return;

  int maxPlace = (log(dec) / log(2));
  digitalWrite(leds[maxPlace], HIGH);

  int i = maxPlace;
  while (i >= 0) {
    int placeValue = (int) (pow(2, i) + 0.5);

    if (dec >= placeValue) {
      digitalWrite(leds[i], HIGH);
      dec = dec - placeValue;
    }

    i--;
  }

  int guess = 0;
  boolean guessLock = false;
  boolean completeLock = false;

  while (true) {
    buttonState = digitalRead(guessButton);
    complete = digitalRead(completeButton);

    if (complete == LOW && !completeLock) {
      if (guess == orig) {
        correct();
        inARow++;
        if (inARow >= winNum) {
          win();
          inARow = 0;
        }
        break;
      } else {
        wrong();
        inARow = 0;
      }
      completeLock = true;
      guess = 0;
    } else if (complete == HIGH) {
      completeLock = false;
      delay(50);
    }

    if (buttonState == LOW && !guessLock) {
      guessLock = true;
      guess++;
    } else if (buttonState == HIGH) {
      guessLock = false;
      delay(50);
    }
  }
}

void lights(int state) {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], state);
  }
}

void correct() {
  tone(buzz, 300, 150);
  delay(150);
  tone(buzz, 400, 200);
  delay(200);
}

void wrong() {
  tone (buzz, 100, 300);
  delay(300);
}

void win() {
  lights(LOW);
  digitalWrite(led1, HIGH);
  tone(buzz, 523, 100);
  delay(100);

  lights(LOW);
  tone(buzz, 587, 100);
  digitalWrite(led2, HIGH);
  delay(100);

  lights(LOW);
  tone(buzz, 659, 100);
  digitalWrite(led3, HIGH);
  delay(100);

  lights(LOW);
  tone(buzz, 698, 100);
  digitalWrite(led4, HIGH);
  delay(100);

  lights(HIGH);
  tone(buzz, 783, 500);
  digitalWrite(led1, HIGH);
  delay(500);
}
