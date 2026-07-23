#pragma once
#include "CommonLibraries.h"

#define PI 3.1415927

class Cylinders {

public:
    /* https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6 */
    void drawCylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B);
};

class Cubes {
    

public:
    void drawCube(double r, double g, double b);
};

class Rectangles {

public:
    void drawRectangle(double width, double length, double height, double r, double g, double b);
};

class Pyramid {

public:
    void drawPyramid(double width, double length, double height, double r, double g, double b);
};