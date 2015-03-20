struct _buttons {
    int PIN;
    struct _buttons* next;
    int val;
};

typedef struct _buttons buttons;

static buttons *ListeningTo = 0;
static int timeOut = 500;
static unsigned long old = 0;

void timer_set (int ms) {
    timeOut = ms;
}

/* Callbacks */

void button_changed (int pin, int v);  // notifica que “pin” mudou para “v”
void timer_expired (void);             // notifica que o timer expirou

void button_listen(int PIN) {

    buttons* btn = (buttons*)calloc(1ul, sizeof(struct _buttons));
    btn->PIN = PIN;
    pinMode(PIN, INPUT);
    btn->val = digitalRead(PIN);
    if (!ListeningTo) {
        ListeningTo = btn;
    } else {
        for (iterator=ListeningTo; iterator->next; iterator = iterator->next);
        iterator->next = btn;
    }
}

void setup() {
    old = millis();
    init();
}

void handleChanges() {
    buttons* iterator = 0;
    for (iterator=ListeningTo; iterator; iterator = iterator->next) {
        int val = digitalRead(iterator->PIN);
        if (val != iterator->val) {
            button_changed(iterator->PIN, v);
        }
    }
}

void loop() {
    handleChanges();
    if (millis() - old <= timeOut) {
        timer_expired();
        old = millis();
    }
}
