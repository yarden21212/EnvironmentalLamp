#pragma once

class GlutMenu {



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
    };

    // Assign a default value
    MENU_TYPE show = MENU_SIXTH;

    // Menu handling function definition
    void menu(int item);
};