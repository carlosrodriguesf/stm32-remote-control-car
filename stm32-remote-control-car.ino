#include <Arduino.h>
#include <jled.h>
#include "gamepad.cpp"

Gamepad gamepad(&Serial2);

int ledPinArrowRight = PB8;
int ledPinArrowLeft = PB9;

auto jledArrowRight = JLed(ledPinArrowRight).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
auto jledArrowLeft = JLed(ledPinArrowLeft).Breathe(1000).Repeat(6).DelayAfter(100).Stop();

typedef struct {
    bool arrowRight;
    bool arrowLeft;
    bool alert;
    int headlight; // 0 - none | 1 - low beam | 2 - high beam
} State;

State state;

bool setuprun = false;

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600);

    gamepad.setDebugEnabled(true);

    pinMode(ledPinArrowLeft, OUTPUT);
    pinMode(ledPinArrowRight, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
    state.arrowRight = false;
    state.arrowLeft = false;
    state.alert = false;

    setuprun = true;
}

void loop() {
    jledArrowLeft.Update();
    jledArrowRight.Update();
    if (!gamepad.update()) {
        return;
    }

    updateState();

    if (state.arrowLeft) {
        jledArrowLeft = JLed(ledPinArrowLeft).Breathe(1000).Repeat(6).DelayAfter(100).Forever();
    } else {
        jledArrowLeft = JLed(ledPinArrowLeft).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
    }

    if (state.arrowRight) {
        jledArrowRight = JLed(ledPinArrowRight).Breathe(1000).Repeat(6).DelayAfter(100).Forever();
    } else {
        jledArrowRight = JLed(ledPinArrowRight).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
    }
}

void updateState() {
    GamepadConfig current = gamepad.current();

    if (!state.alert && current.buttonRB) {
        state.arrowRight = !state.arrowRight;
        state.arrowLeft = false;
    }
    if (!state.alert && current.buttonLB) {
        state.arrowLeft = !state.arrowLeft;
        state.arrowRight = false;
    }
    if (current.buttonY) {
        state.alert = !state.alert;
        state.arrowLeft = state.alert;
        state.arrowRight = state.alert;
    }
    if (current.buttonA) {
        state.headlight += 1;
        if (state.headlight >= 2) {
            state.headlight = 0;
        }
    }
}


///////////////////////////////////////////////////////////////////
void debug() {
    Serial.println("CURRENT -----------------------");
    debugConfig(gamepad.current());
    Serial.println("PREVIOUS ----------------------");
    debugConfig(gamepad.previous());
    delay(500);
}

void debugConfig(GamepadConfig config) {
    printBoolln("Button A", config.buttonA);
    printBoolln("Button B", config.buttonB);
    printBoolln("Button Y", config.buttonY);
    printBoolln("Button X", config.buttonX);
    printBoolln("Button RB", config.buttonRB);
    printBoolln("Button LB", config.buttonLB);
    printBoolln("Button thumb R", config.buttonThumbR);
    printBoolln("Button thumb L", config.buttonThumbL);
    printIntln("Axis LY", config.axisLY);
    printIntln("Axis LX", config.axisLX);
    printIntln("Axis RY", config.axisRY);
    printIntln("Axis RX", config.axisRX);
    printIntln("Axis LT", config.axisLT);
    printIntln("Axis RT", config.axisRT);
    printIntln("Axis RT", config.axisRT);
    printIntln("Axis RT", config.axisRT);
}

void printIntln(String name, int value) {
    String s;
    s.concat(value);
    println(name, s);
}

void printBoolln(String name, bool value) {
    if (value) {
        println(name, "true");
    } else {
        println(name, "false");
    }
}

void println(String name, String value) {
    Serial.print(name);
    Serial.print(" : ");
    Serial.println(value);
}
