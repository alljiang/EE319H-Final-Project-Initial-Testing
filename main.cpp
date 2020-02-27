
#include <iostream>
#include <SDL.h>
#include <windows.h>
#include <fcntl.h>

#include "LCD.h"
#include "controller.h"
#include "utils.h"
#include "UART.h"
#include "metadata.h"
#include "SRAM.h"

using namespace std;
using namespace chrono;

SDL_Event event;

bool quit;

float x = 0;
float y = 0;

char strBuffer[100];
long long lastLoopMillis;

//  runs once at beginning
void startup() {
    animator_initialize();
    UART_readCharacterSDCard(0);

    SpriteSendable s;
    s.persistent = false;
    s.charIndex = 0;
    s.animationIndex = 0;
    s.x = 0;
    s.y = 0;
    s.frame = 0;
    s.layer = LAYER_CHARACTER;

    UART_sendAnimation(s);
}

//  continually loops
uint32_t  t1 = 0;
void loop() {
//    float dt = millis() - lastLoopMillis;
//    lastLoopMillis = millis();
//
//    float pps = 100.;
//    x += getJoystick_h(1) * pps * dt / 1000.;
//    y += getJoystick_v(1) * pps * dt / 1000.;
//
//    LCD_drawPixel(x, y, 0x00FF00);
    if(millis() - t1 > 2000) {
        printf("LOOP\n");
        t1 = millis();
        animator_update();
    }
    LCD_update();
}

int main(int argc, char *argv[]) {
    LCD_startLCD();

    // Print console setup
    AllocConsole();
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;
    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;

    SRAM_reset();
    startup();

    //  wait for window to close
    while (!quit)
    {
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        controller_updateController();
        loop();
    }

    stopSDL2();

    return EXIT_SUCCESS;
}
