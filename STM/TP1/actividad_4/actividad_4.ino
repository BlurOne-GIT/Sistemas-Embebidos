#define L1 PB4
#define L2 PB5
#define L3 PB6
#define L4 PB7
#define L5 PB8
#define L6 PB9
#define S2 PB14
#define POT PA0
#define ANALOG_MAX 4096
#define ANALOG_DIV 682

void setup() {
  // put your setup code here, to r
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
  pinMode(S2, INPUT);
  pinMode(POT, INPUT_ANALOG);
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  int lights;
  if (digitalRead(S2) == LOW)
    lights = 0;
  else
    lights = analogRead(POT) / ANALOG_DIV;
  
  for (int i = 0; i < 6; ++i)
    digitalWrite(L1+i, i+1 <= lights ? HIGH : LOW);
}
