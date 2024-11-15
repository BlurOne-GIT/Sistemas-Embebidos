#define L3 PB6
#define LDR PA1

void setup() {
  // put your setup code here, to run once:
  pinMode(PB5, OUTPUT);
  pinMode(LDR, INPUT_ANALOG);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  analogWrite(L3, analogRead(LDR) >> 4);
}
