#define R PB14
#define A PB13
#define V PB12
#define BTN1 PA0
#define BTN2 PA1
#define BUZ PA9
#define StateV 0
#define StateA 1
#define StateR 2
#define StateRA 3

char state = StateV;
bool emergency = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(R, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(V, OUTPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BUZ, OUTPUT);
  attachInterrupt(BTN1, peatonInterrupt, RISING);
  attachInterrupt(BTN2, emergencyInterrupt, RISING);
  Serial.begin(115200);
  setState(StateV);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void peatonInterrupt() {
  setState(state == StateV ? StateA : StateR);
}

void emergencyInterrupt() {
  emergency = !emergency;
  digitalWrite(BUZ, emergency);
  if (emergency)
    Serial.println("Ayuda policia!!1!");
  setState(emergency ? StateR : StateRA);
}

void setState(char newState) {
  state = newState;
  digitalWrite(R, state == StateR || state == StateRA);
  digitalWrite(A, state == StateA || state == StateRA);
  digitalWrite(V, state == StateV);
  if (state == StateRA || state == StateA || (!emergency && state == StateR))
    setTimer(state == StateR ? 5 : 2, advanceTrafficLight);
}

void advanceTrafficLight() {
  Timer1.pause();
  setState((state+1)%4);
}

void setTimer(int seconds, voidFuncPtr function)
{
  Timer1.pause();
  Timer1.setPeriod(seconds*1000000);
  Timer1.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  Timer1.setCompare(TIMER_CH1, -1);
  Timer1.attachInterrupt(TIMER_CH1, function);
  Timer1.refresh();
  Timer1.resume();
}
