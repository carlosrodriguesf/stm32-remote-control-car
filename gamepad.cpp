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

typedef struct {
    int key;
    int value;
} Command;

typedef struct {
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
} GamepadConfig;

class Gamepad {
public:
    Gamepad(HardwareSerial *serial) {
        this->serial = serial;
        this->skipCounter = 0;

        GamepadConfig init;
    }

    GamepadConfig current() {
        return this->currentConfiguration;
    }

    GamepadConfig previous() {
        return this->previousConfiguration;
    }

    void setDebugEnabled(bool enabled) {
        this->debugEnabled = enabled;
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

        Command command = this->readCommand();

        if (this->debugEnabled) {
            Serial.print("COMMAND : ");
            Serial.print(command.key);
            Serial.print(" : ");
            Serial.print(command.value);
            Serial.println(";");
        }

        this->updateConfig(command.key, command.value);
        return true;
    }

private:
    HardwareSerial *serial;
    int skipCounter;
    bool debugEnabled;
    GamepadConfig currentConfiguration;
    GamepadConfig previousConfiguration;

    void updateConfig(int button, int value) {
        this->previousConfiguration = this->currentConfiguration;

        GamepadConfig *config = &this->currentConfiguration;

        switch (button) {
            case BUTTON_A:
                config->buttonA = value == 1;
                break;
            case BUTTON_B:
                config->buttonB = value == 1;
                break;
            case BUTTON_Y:
                config->buttonY = value == 1;
                break;
            case BUTTON_X:
                config->buttonX = value == 1;
                break;
            case BUTTON_RB:
                config->buttonRB = value == 1;
                break;
            case BUTTON_LB:
                config->buttonLB = value == 1;
                break;
            case BUTTON_THUMB_L:
                config->buttonThumbL = value == 1;
                break;
            case BUTTON_THUMB_R:
                config->buttonThumbR = value == 1;
                break;
            case AXIS_LY:
                config->axisLY = value;
                break;
            case AXIS_LX:
                config->axisLX = value;
                break;
            case AXIS_RY:
                config->axisRY = value;
                break;
            case AXIS_RX:
                config->axisRX = value;
                break;
            case AXIS_LT:
                config->axisLT = value;
                break;
            case AXIS_RT:
                config->axisRT = value;
                break;
        }
    }

    void clean() {
        while (this->serial->available()) {
            this->serial->read();
        }
    }

    Command readCommand() {
        String content = readCommandString();
        Command command;
        command.key = content.substring(0, 2).toInt();
        command.value = content.substring(2, 5).toInt();
        if (content.charAt(5) == '0') {
            command.value = command.value *= -1;
        }
        return command;
    }

    String readCommandString() {
        String content;
        do {
            if (!serial->available()) {
                continue;
            }
            content.concat((char) this->serial->read());
        } while (!content.endsWith(";"));
        return content;
    }
};
