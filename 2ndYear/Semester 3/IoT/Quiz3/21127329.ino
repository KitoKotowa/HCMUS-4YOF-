// C++ code
// 21127329
// Châu Tấn Kiệt
// 21CLC04

int photoresistor = A0;
int sensor = 0;
int relay = 8;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(photoresistor, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensor = analogRead(photoresistor);
  Serial.println(sensor);                     
  
  if (sensor < 300){
    digitalWrite(relay, HIGH); // Turn relay on
  } else{ 
    digitalWrite(relay, LOW); // Turn relay off
  }
  
  delay(500);
}