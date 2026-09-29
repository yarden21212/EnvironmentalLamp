#pragma once

#include "Music.h"


class GlutMenu {

private:
    Music music;

public:
    // Menu items
    enum MENU_TYPE
    {
        MENU_FIRST,
        MENU_SECOND,
        MENU_THIRD,
        MENU_FOURTH,
        MENU_FIFTH,
        MENU_SIXTH,
        MENU_SEVENTH,
        MENU_EIGHTH,
        MENU_NINTH,
    };

    // Assign a default value
    MENU_TYPE show = MENU_SIXTH;

    // Menu handling function definition
    void menu(int item);
};