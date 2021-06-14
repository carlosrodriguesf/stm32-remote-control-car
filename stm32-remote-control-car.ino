#include <Arduino.h>
#include <jled.h>
#include <Servo.h>
#include "gamepad.cpp"

const int DIRECTION_NONE = 0;
const int DIRECTION_FRONT = 1;
const int DIRECTION_BACK = 2;

Gamepad gamepad(&Serial2);

const int pinLedArrowRight = PB8;
const int pinLedArrowLeft = PB9;
const int pinLedHeadlight = PB7;
const int pinServoDirection = PB6;
const int pinMotorPower = PA8;
const int pinMotorInput1 = PB15;
const int pinMotorInput2 = PB14;

auto jledArrowRight = JLed(pinLedArrowRight).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
auto jledArrowLeft = JLed(pinLedArrowLeft).Breathe(1000).Repeat(6).DelayAfter(100).Stop();
Servo servoDirection;

typedef struct {
    bool arrowRight;
    bool arrowLeft;
    bool alert;

    bool headlightOn; // 0 - none | 1 - low beam | 2 - high beam
    bool highBeam;

    int headlight;
    int axisDirection;
    int motorDirection; // 0 - none | 1 - front | 2 - back
    int motorPower;
} State;

State state;
State prevState;

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200);

    gamepad.setDebugEnabled(true);

    pinMode(pinLedArrowLeft, OUTPUT);
    pinMode(pinLedArrowRight, OUTPUT);
    pinMode(pinLedHeadlight, PWM);
    pinMode(pinMotorPower, PWM);
    pinMode(pinMotorInput1, OUTPUT);
    pinMode(pinMotorInput2, OUTPUT);

    servoDirection.attach(pinServoDirection);

    state.arrowRight = false;
    state.arrowLeft = false;
    state.alert = false;
    state.headlightOn = false;
    state.highBeam = false;
    state.headlight = 0;
    state.axisDirection = 90;
    state.motorDirection = 0;
    state.motorPower = 0;

    applyState();

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    jledArrowLeft.Update();
    jledArrowRight.Update();
    if (!gamepad.update()) {
        return;
    }

    processNewState();
    applyState();
}

void applyState() {
    if (prevState.arrowLeft != state.arrowLeft) {
        if (state.arrowLeft) {
            jledArrowLeft = JLed(pinLedArrowLeft).Breathe(1000).DelayAfter(100).Forever();
        } else {
            jledArrowLeft = JLed(pinLedArrowLeft).Breathe(1000).DelayAfter(100).Stop();
        }
    }

    if (prevState.arrowRight != state.arrowRight) {
        if (state.arrowRight) {
            jledArrowRight = JLed(pinLedArrowRight).Breathe(1000).DelayAfter(100).Forever();
        } else {
            jledArrowRight = JLed(pinLedArrowRight).Breathe(1000).DelayAfter(100).Stop();
        }
    }

    pwmWrite(pinLedHeadlight, map(state.headlight, 0, 2, 0, 65535));
    servoDirection.write(state.axisDirection);

    digitalWrite(pinMotorInput1, state.motorDirection == DIRECTION_FRONT && state.motorDirection != DIRECTION_NONE);
    digitalWrite(pinMotorInput2, state.motorDirection == DIRECTION_BACK && state.motorDirection != DIRECTION_NONE);
    pwmWrite(pinMotorPower, map(state.motorPower, 0, 1000, 0, 65535));
}

void processNewState() {
    prevState = state;

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
        state.headlightOn = !state.headlightOn;
    }
    if (current.buttonB) {
        state.highBeam = !state.highBeam;
    }
    if (state.headlightOn) {
        state.headlight = ((int)state.headlightOn) + ((int)state.highBeam);
    } else {
        state.headlight = 0;
    }

    Serial.println(state.headlight);

    state.axisDirection = map(current.axisLX, -100, 100, 0, 180);

    int axisLT = map(current.axisLT, 0, 100, 0, 1000);
    int axisRT = map(current.axisRT, 0, 100, 0, 1000);
    state.motorPower = axisLT - axisRT;
    if (state.motorPower > 0) {
        state.motorDirection = DIRECTION_FRONT;
    } else if (state.motorPower < 0) {
        state.motorDirection = DIRECTION_BACK;
        state.motorPower *= -1;
    } else {
        state.motorDirection = DIRECTION_NONE;
    }
    if (state.motorPower < 10) {
        state.motorPower = 0;
    }
}