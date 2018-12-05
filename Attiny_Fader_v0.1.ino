int val = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = (analogRead(A2)) / 4;
  while (val > 70 && val < 60)
  {
    if (val > 64) {
      digitalWrite(3, HIGH);
      digitalWrite(1, LOW);
    }
    if (val < 60) {
      digitalWrite(1, HIGH);
      digitalWrite(3, LOW);
    }
  }
}
