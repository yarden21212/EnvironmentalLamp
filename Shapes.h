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
    void drawCube(float r, float g, float b);
};

class Rectangles {

public:
    void drawRectangle(float width, float length, float height, float r, float g, float b, GLuint texture);
};

class Pyramid {

public:
    void drawPyramid(float width, float length, float height, GLubyte r, GLubyte g, GLubyte b);
};