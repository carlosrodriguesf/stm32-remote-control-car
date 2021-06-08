#include <Arduino.h>

const int BUTTON_A = 1;
const int BUTTON_B = 2;
const int BUTTON_Y = 3;
const int BUTTON_X = 4;
const int BUTTON_LB = 5;
const int BUTTON_RB = 6;
const int BUTTON_THUMB_L = 7;
const int BUTTON_THUMB_R = 8;
const int AXIS_LY = 9;
const int AXIS_LX = 10;
const int AXIS_RY = 11;
const int AXIS_RX = 12;
const int AXIS_LT = 13;
const int AXIS_RT = 14;

class Gamepad {
public:
    bool buttonA;
    bool buttonB;
    bool buttonY;
    bool buttonX;
    bool buttonLB;
    bool buttonRB;
    bool buttonThumbL;
    bool buttonThumbR;
    int axisLY;
    int axisLX;
    int axisRY;
    int axisRX;
    int axisLT;
    int axisRT;

    Gamepad(HardwareSerial *serial) {
        this->serial = serial;
    }

    bool update() {
        if (!this->serial->available()) {
            this->skipCounter++;
            if (this->skipCounter == 100) {
                this->clean();
                this->skipCounter = 0;
            }
            return false;
        }

        int head = this->getHead();
        int value = this->getValue();

        switch (head) {
            case BUTTON_A:
                this->buttonA = value == 1;
                break;
            case BUTTON_B:
                this->buttonB = value == 1;
                break;
            case BUTTON_Y:
                this->buttonY = value == 1;
                break;
            case BUTTON_X:
                this->buttonX = value == 1;
                break;
            case BUTTON_RB:
                this->buttonRB = value == 1;
                break;
            case BUTTON_LB:
                this->buttonLB = value == 1;
                break;
            case BUTTON_THUMB_L:
                this->buttonThumbL = value == 1;
                break;
            case BUTTON_THUMB_R:
                this->buttonThumbR = value == 1;
                break;
            case AXIS_LY:
                this->axisLY = value;
                break;
            case AXIS_LX:
                this->axisLX = value;
                break;
            case AXIS_RY:
                this->axisRY = value;
                break;
            case AXIS_RX:
                this->axisRX = value;
                break;
            case AXIS_LT:
                this->axisLT = value;
                break;
            case AXIS_RT:
                this->axisRT = value;
                break;
        }

        return true;
    }

private:
    HardwareSerial *serial;
    int skipCounter = 0;

    void clean() {
        while (this->serial->available()) {
            this->serial->read();
        }
    }

    int getValue() {
        int value = this->readInt(3);
        if (this->readInt(1) == 0) {
            value *= -1;
        }
        return value;
    }

    int getHead() {
        return this->readInt(2);
    }

    int readInt(int size) {
        String content;
        int index = 0;
        do {
            if (!this->serial->available()) {
                continue;
            }
            content.concat((char) this->serial->read());
            index++;
        } while (index < size);
        return content.toInt();
    }
};
