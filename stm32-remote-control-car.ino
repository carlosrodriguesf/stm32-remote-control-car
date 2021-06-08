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
} State;

State state;

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600);

    pinMode(ledPinArrowLeft, OUTPUT);
    pinMode(ledPinArrowRight, OUTPUT);

    state.arrowRight = false;
    state.arrowLeft = false;
    state.alert = false;

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILDIN, HIGH);

    Serial.println("System started");
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
    if (gamepad.buttonRB) {
        Serial.println("buttonRB");
        state.arrowRight = !state.arrowRight;
        state.arrowLeft = false;
    }
    if (gamepad.buttonLB) {
        Serial.println("buttonLB");
        state.arrowLeft = !state.arrowLeft;
        state.arrowRight = false;
    }
    if (gamepad.buttonA) {
        Serial.println("buttonA");
        state.alert = !state.alert;
        state.arrowLeft = state.alert;
        state.arrowRight = state.alert;
    }
}


///////////////////////////////////////////////////////////////////
void debug() {
    Serial.println("-----------------------");
    printBoolln("Button A", gamepad.buttonA);
    printBoolln("Button B", gamepad.buttonB);
    printBoolln("Button Y", gamepad.buttonY);
    printBoolln("Button X", gamepad.buttonX);
    printBoolln("Button RB", gamepad.buttonRB);
    printBoolln("Button LB", gamepad.buttonLB);
    printBoolln("Button thumb R", gamepad.buttonThumbR);
    printBoolln("Button thumb L", gamepad.buttonThumbL);
    printIntln("Axis LY", gamepad.axisLY);
    printIntln("Axis LX", gamepad.axisLX);
    printIntln("Axis RY", gamepad.axisRY);
    printIntln("Axis RX", gamepad.axisRX);
    printIntln("Axis LT", gamepad.axisLT);
    printIntln("Axis RT", gamepad.axisRT);
    printIntln("Axis RT", gamepad.axisRT);
    printIntln("Axis RT", gamepad.axisRT);
    delay(500);
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
