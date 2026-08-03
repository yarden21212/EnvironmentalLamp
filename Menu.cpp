/* How to create a Menu */

#include "Menu.h"
#include "CommonLibraries.h"
#include "GlobalVariables.h"

#include <GL/freeglut.h>


// Global menu instance (if needed)
extern GlutMenu gMenu;



void GlutMenu::menu(int item)
{
    switch (item)
    {
    case MENU_FIRST:
    {
        cameraX = -2.6f, cameraY = 1.3f, cameraZ = -0.2f;
        targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;
        upX = 0.0f, upY = 1.0f, upZ = 0.0f;
        xwMin = -1.0f, ywMin = -1.0f, xwMax = 1.0f, ywMax = 1.0f;
        nearPlane = 1.0f, farPlane = 30.0f;

        rotateDegreeMain = 0;
        rotateDegreeSecond = 0;
        rotateDegreeTopHinge = 0;

        /* Bulb: */
        lightOn = false;

        /* Books */
        bookMovementDegree;

    }
    case MENU_SECOND:
    case MENU_THIRD:  
    case MENU_FOURTH:
    case MENU_FIFTH:
    case MENU_SIXTH:
    {
        show = (MENU_TYPE)item;
    }
    break;
    default:
    {       /* Nothing */ }
    break;
    }

    glutPostRedisplay();

    return;
}