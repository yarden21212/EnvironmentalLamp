#include "Shapes.h"

/* https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6 */
void Cylinders::drawCylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B) {
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R - 40, G - 40, B - 40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void Cubes::drawCube(double r, double g, double b){

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        // Bottom face (y = -1.0f)
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        // Front face  (z = 1.0f)
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        // Left face (x = -1.0f)
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        // Right face (x = 1.0f)
        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
}
void Rectangles::drawRectangle(double width, double length, double height, double r, double g, double b) {

    float halfWidth = width / 2;
    float halfLength = length / 2;
    float top = height / 2;

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        glColor3f(r, g, b);
        glVertex3f(-halfWidth, top, -halfLength);
        glVertex3f(halfWidth, top, -halfLength);
        glVertex3f(halfWidth, top, halfLength);
        glVertex3f(-halfWidth, top, halfLength);

        // Bottom face (y = -1.0f)
        //glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glVertex3f(-halfWidth, -top, -halfLength);
        glVertex3f(halfWidth, -top, -halfLength);
        glVertex3f(halfWidth, -top, halfLength);
        glVertex3f(-halfWidth, -top, halfLength);

        // Front face  (z = 1.0f)
        //glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f(halfWidth, top, halfLength);
        glVertex3f(-halfWidth, top, halfLength);
        glVertex3f(-halfWidth, -top, halfLength);
        glVertex3f(halfWidth, -top, halfLength);

        // Back face (z = -1.0f)
        //glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glVertex3f(halfWidth, -top, -halfLength);
        glVertex3f(-halfWidth, -top, -halfLength);
        glVertex3f(-halfWidth, top, -halfLength);
        glVertex3f(halfWidth, top, -halfLength);

        // Left face (x = -1.0f)
        //glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(-halfWidth, top, halfLength);
        glVertex3f(-halfWidth, top, -halfLength);
        glVertex3f(-halfWidth, -top, -halfLength);
        glVertex3f(-halfWidth, -top, halfLength);

        // Right face (x = 1.0f)
/*        glColor3f(r, g, b);   */  
        glVertex3f(halfWidth, top, -halfLength);
        glVertex3f(halfWidth, top, halfLength);
        glVertex3f(halfWidth, -top, halfLength);
        glVertex3f(halfWidth, -top, -halfLength);
    glEnd();  // End of drawing color-cube
}

void Pyramid::drawPyramid(double width, double length, double height, double r, double g, double b) {

    float halfWidth = width / 2;
    float halfLength = length / 2;
    float top = height / 2;

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
    // Front
    glColor3ub(r, g, b);
    glVertex3f(0.0f, halfLength, 0.0f);
    glVertex3f(-halfWidth, -halfLength, top);
    glVertex3f(halfWidth, -halfLength, top);

    // Right
    glVertex3f(0.0f, halfLength, 0.0f);
    glVertex3f(halfWidth, -halfLength, top);
    glVertex3f(halfWidth, -halfLength, -top);

    // Back
    glVertex3f(0.0f, halfLength, 0.0f);
    glVertex3f(halfWidth, -halfLength, -top);
    glVertex3f(-halfWidth, -halfLength, -top);

    // Left
    glVertex3f(0.0f, halfLength, 0.0f);
    glVertex3f(-halfWidth, -halfLength, -top);
    glVertex3f(-halfWidth, -halfLength, top);
    glEnd();   // Done drawing the pyramid
}