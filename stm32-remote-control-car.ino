#include <Arduino.h>
#include <jled.h>
#include <Servo.h>
#include "gamepad.cpp"

Gamepad gamepad(&Serial2);

const int pinLedArrowRight = PB8;
const int pinLedArrowLeft = PB9;
const int pinLedHeadlight = PB7;
const int pinServoDirection = PB6;

auto jledArrowRight = JLed(pinLedArrowRight).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
auto jledArrowLeft = JLed(pinLedArrowLeft).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
Servo servoDirection;

typedef struct {
    bool arrowRight;
    bool arrowLeft;
    bool alert;
    int headlight; // 0 - none | 1 - low beam | 2 - high beam
    int direction;
} State;

State state;

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600);

    gamepad.setDebugEnabled(true);

    pinMode(pinLedArrowLeft, OUTPUT);
    pinMode(pinLedArrowRight, OUTPUT);
    pinMode(pinLedHeadlight, PWM);

    servoDirection.attach(pinServoDirection);

    digitalWrite(pinLedArrowLeft, LOW);
    digitalWrite(pinLedArrowRight, LOW);
    digitalWrite(pinLedHeadlight, LOW);

    state.arrowRight = false;
    state.arrowLeft = false;
    state.alert = false;
    state.headlight = 0;
    state.direction = 90;

    syncState();

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    jledArrowLeft.Update();
    jledArrowRight.Update();
    if (!gamepad.update()) {
        return;
    }

    updateState();
    syncState();
}

void syncState() {
    if (state.arrowLeft) {
        jledArrowLeft = JLed(pinLedArrowLeft).Breathe(1000).Repeat(6).DelayAfter(100).Forever();
    } else {
        jledArrowLeft = JLed(pinLedArrowLeft).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
    }

    if (state.arrowRight) {
        jledArrowRight = JLed(pinLedArrowRight).Breathe(1000).Repeat(6).DelayAfter(100).Forever();
    } else {
        jledArrowRight = JLed(pinLedArrowRight).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
    }

    pwmWrite(pinLedHeadlight, map(state.headlight, 0, 2, 0, 65535));
    servoDirection.write(state.direction);

    Serial.println(state.direction);
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
        if (state.headlight > 2) {
            state.headlight = 0;
        }
    }

    state.direction = map(current.axisLX, -100, 100, 0, 180);
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
