#define L1 PB4
#define L2 PB5
#define L3 PB6
#define P1 PB12

char count = 0;
bool waitRelease = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(P1, INPUT_PULLUP);
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(P1) == LOW && !waitRelease)
  {
    waitRelease = true;
    delay(50);
    return;
  }

  if (digitalRead(P1) != HIGH || !waitRelease)
  {
    delay(50);
    return;
  }

  waitRelease = false;

  if (++count == 4)
  {
    count = 0;
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    return;
  }

  if (count == 1)
    digitalWrite(L1, HIGH);
  
  if (count == 2)
    digitalWrite(L2, HIGH);

  if (count == 3)
    digitalWrite(L3, HIGH);
}
