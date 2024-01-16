
// C++ code
//
int redLed = 10;
int greenLed = 9;
int yellowLed = 8;

void setup()
{
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
}

void loop()
{
  digitalWrite(redLed, HIGH);
  delay(9000); // Wait 9 seconds
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  delay(6000); // Wait 6 seconds
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, HIGH);
  delay(3000); // Wait 3 seconds
  digitalWrite(yellowLed, LOW);
}