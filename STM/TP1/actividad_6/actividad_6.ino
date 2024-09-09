#define L1 PB4
#define L2 PB5
#define L3 PB6
#define L4 PB7
#define L5 PB8
#define L6 PB9
#define P1 PB12
#define P2 PB13
#define S1 PB15
#define S2 PB14
#define POT PA0
#define LDR PA1

char mode = 0;
bool waitRelease = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(POT, INPUT_ANALOG);
  pinMode(LDR, INPUT_ANALOG);
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
}

void loop() {
  delay(50);
  if (!waitRelease && digitalRead(P1) && digitalRead(P2))
    waitRelease = true;
  if (waitRelease && (!digitalRead(P1) || !digitalRead(P2))) {
    waitRelease = false;
    ++mode;
    mode %= 5;  
  }
  // put your main code here, to run repeatedly:
  switch (mode) {
    case 0: mode1(); break;
    case 1: mode2(); break;
    case 2: mode3(); break;
    case 3: mode4(); break;
    case 4: mode5(); break;
  }
}

void mode1() {
  for (int i = 0; i < 6; ++i)
    digitalWrite(L1 + i, HIGH);
}

void mode2() {
  uint8 odd = !digitalRead(P1);
  digitalWrite(L1, odd);
  digitalWrite(L3, odd);
  digitalWrite(L5, odd);
  uint8 even = !digitalRead(P1);
  digitalWrite(L2, odd);
  digitalWrite(L4, odd);
  digitalWrite(L6, odd);
}

void mode3() {
  uint8 bottom = digitalRead(S1);
  digitalWrite(L1, bottom);
  digitalWrite(L2, bottom);
  digitalWrite(L3, bottom);
  uint8 top = digitalRead(S1);
  digitalWrite(L4, top);
  digitalWrite(L5, top);
  digitalWrite(L6, top);
}

void mode4() {
  int value = analogRead(POT) >> 4;
  analogWrite(L5, value);
  if (digitalRead(S1))
    analogWrite(L4, value);
  if (digitalRead(S2))
    analogWrite(L6, value);
}

void mode5() {
  analogWrite(L3, analogRead(LDR) >> 4);
}