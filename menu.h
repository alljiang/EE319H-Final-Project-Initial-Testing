//
// Created by Allen on 4/28/2020.
//

#ifndef EE319K_FINAL_PROJECT_INITIAL_TESTING_MENU_H
#define EE319K_FINAL_PROJECT_INITIAL_TESTING_MENU_H

#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"

class Menu {

    #define MENU_CURSORSPEED 6

public:
    double l_joyH1;              //  P1 last joystick horizontal value
    double l_joyV1;              //  P1 last joystick vertical value
    bool l_btnA1;                //  P1 last button A value
    bool l_btnB1;                //  P1 last button B value
    double l_joyH2;              //  P2 last joystick horizontal value
    double l_joyV2;              //  P2 last joystick vertical value
    bool l_btnA2;                //  P2 last button A value
    bool l_btnB2;                //  P2 last button B value

    void start();
    void loop(double joyH1, double joyV1, double joyH2, double joyV2,
              bool btnA1, bool btnA2, bool btnB1, bool btnB2);
    void reset();
    void updateLastValues(double joyH1, double joyV1, double joyH2, double joyV2,
                          bool btnA1, bool btnA2, bool btnB1, bool btnB2);

    int8_t getCharacter(double x, double y);

    uint8_t charIndex = 4;

    bool p1Selected, p2Selected;
    long long currentTime;

    double p1CursorX;
    double p1CursorY;
    double p2CursorX;
    double p2CursorY;
};


#endif //EE319K_FINAL_PROJECT_INITIAL_TESTING_MENU_H
