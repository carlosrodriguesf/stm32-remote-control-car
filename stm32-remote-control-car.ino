#include <Arduino.h>
#include <jled.h>
#include "gamepad.cpp"

Gamepad gamepad(&Serial2);

int pinA = PB8;
int pinB = PB9;
int TX = PA3;
int RX = PA2;

auto led_breathe = JLed(pinA).Breathe(1000).Repeat(6).DelayAfter(100).Forever();
int incomingByte;

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600);

    pinMode(pinB, OUTPUT);
    pinMode(pinA, OUTPUT);
}

void loop() {
    led_breathe.Update();

    if (!gamepad.update()) {
      return;
    }

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
