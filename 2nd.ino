#define LED_PIN 13
#define BUT_SLW 2
#define BUT_PIN 4

bool state = 1;
long tBtP, tBtS;
unsigned long t, old;

inline void initPins() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_SLW, INPUT);
  pinMode(BUT_PIN, INPUT);

}

void setup() {
  tBtP = -10000;
  tBtS = -20000;
  t = 1000;
  
  old = millis();
  digitalWrite(LED_PIN, state);
}

void loop() {
  //saving time from now
  unsigned long now = millis();
  
  // case time enough has passed, then:
  if (now >= old + t) {
    old = now;
    state = !state;
    digitalWrite(LED_PIN, state);
  }
  
  if (digitalRead(BUT_PIN)) {
    t *= 2;
    tBtP = now;
  }
  
  if (digitalRead(BUT_SLW)) {
    t /= 2;
    tBtS = now;
  }
  
  if (500 > abs(tBtP - tBtS)) {
    while (1);
  }
}
