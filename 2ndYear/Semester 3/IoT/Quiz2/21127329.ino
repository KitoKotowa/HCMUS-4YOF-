
// C++ code

int trig_pin = 2;
int echo_pin = 3;

int led1Pin = 4;
int led2Pin = 5;
int led3Pin = 6;
int led4Pin = 7;
int led5Pin = 8;

long getDistance() {
	digitalWrite(trig_pin, LOW); 
  	delayMicroseconds(2); 
  	digitalWrite(trig_pin, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trig_pin, LOW);
  	
  	long duration = pulseIn(echo_pin, HIGH);
  	
  	long distanceCm = duration * 0.034 / 2;
	return distanceCm;
}

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
}

void loop() {
  long distance = getDistance();
  if (distance <= 100) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    digitalWrite(led4Pin, HIGH);
    digitalWrite(led5Pin, HIGH);
  	}
  else if (distance > 100 && distance <= 150) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, HIGH);
      digitalWrite(led3Pin, HIGH);
      digitalWrite(led4Pin, HIGH);
      digitalWrite(led5Pin, LOW);
    } 
  else if (distance > 150 && distance <= 200) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, HIGH);
      digitalWrite(led3Pin, HIGH);
      digitalWrite(led4Pin, LOW);
      digitalWrite(led5Pin, LOW);
    } 
  else if (distance > 200 && distance <= 250) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, HIGH);
      digitalWrite(led3Pin, LOW);
      digitalWrite(led4Pin, LOW);
      digitalWrite(led5Pin, LOW);
    } 
  else {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
      digitalWrite(led3Pin, LOW);
      digitalWrite(led4Pin, LOW);
      digitalWrite(led5Pin, LOW);
    }
}



