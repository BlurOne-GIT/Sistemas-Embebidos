#define L1 PB4
#define L2 PB5
#define L3 PB6
#define S1 PB15
#define S2 PB14

void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
  Serial.begin(115200);
}

void loop() {
  delay(50);
  uint8 wL1 = LOW;
  uint8 wL2 = LOW;
  uint8 wL3 = LOW;
  uint8 rS1 = digitalRead(S1);
  uint8 rS2 = digitalRead(S2);
  switch (rS1 << 1 | rS2) {
    case 0:
      wL1 = HIGH;
    case 1:
      wL2 = HIGH;
    case 2:
      wL3 = HIGH;
      break;
  }
  digitalWrite(L1, wL1);
  digitalWrite(L2, wL2);
  digitalWrite(L3, wL3);
  Serial.println("SW1: " + rS1 + " SW2: " + rS2);
}
