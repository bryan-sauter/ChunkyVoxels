#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "../stdafx.h"

class Globals {

private:

    static const uint16_t g_windowWidth = 1440u;
    static const uint16_t g_windowHeight = 900u;
    static const bool     g_fullScreen = FALSE;

    Globals(){}

public:
    static Globals& getInstance()
    {
        static Globals instance;
        return instance;
    }
    Globals(Globals const&) = delete;
    void operator=(Globals const&) = delete;

    uint16_t getWindowWidth(void) { return g_windowWidth; }
    uint16_t getWindowHeight(void) { return g_windowHeight; }
    bool     getFullScreen(void) { return g_fullScreen; }
};

#endif //GLOBALS_H_
