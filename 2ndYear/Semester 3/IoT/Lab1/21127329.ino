
// C++ code

int button = 2;
int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;
int led5 = 7;
int led6 = 8;

long buttonPressTime = 0;

void setup() {
  pinMode(button, INPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    if (buttonPressTime == 0) {
      buttonPressTime = millis();
    }
    
    //unsigned long buttonHoldTime = millis() - buttonPressTime;
    if (millis()- buttonPressTime < 6000) {
    //Turn on led 4,5 and 6
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    // Blink 1,2,3 for 1 seconds
      digitalWrite(led1, HIGH);
      delay(1000);
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      delay(1000);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      delay(1000);
      digitalWrite(led3, LOW);
    }
    // Check if button is held too long
    // All leds turn on
    if (millis()- buttonPressTime > 6000) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
	}
  }
  else {
    // 1,2,3 on - 4,5,6 off	
 	digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);

    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    //Reset press time
    buttonPressTime = 0;
  }
  
}



