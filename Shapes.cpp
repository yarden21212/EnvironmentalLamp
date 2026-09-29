#include "Shapes.h"

/* https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6  -> Guide to build a cylinder */
void Cylinders::drawCylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B) {
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1f;

    /** Draw the tube */
    glColor3ub(R - 40, G - 40, B - 40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);

        glNormal3f(cos(angle), sin(angle), 0.0f);

        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glNormal3f(1.0f, 0.0f, 0.0f);

    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);

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

void Cubes::drawCube(float r, float g, float b){

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glNormal3d(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        // Bottom face (y = -1.0f)
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glNormal3d(0.0f, -1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        // Front face  (z = 1.0f)
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glNormal3d(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glNormal3d(0.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        // Left face (x = -1.0f)
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glNormal3d(-1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        // Right face (x = 1.0f)
        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glNormal3d(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
}
void Rectangles::drawRectangle(float width, float length, float height, float r, float g, float b, GLuint texture) {


    float halfWidth = width / 2.0f;
    float halfLength = length / 2.0f;
    float top = height / 2.0f;

    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3f(r, g, b);
    glNormal3d(0.0f, 1.0f, 0.0f);

    /* 
        I couldn't figure out how to make the light get stronger as you get closer to the table.
        Until this point, the more centered the light was, the stronger the light gets, and the more you get closer, the darker it is,
        even on the specific point the bulb point on.

        So here I used AI to help me, it suggested to divide the table into many small squares, so now there are many more points.
        So: the points directly below the bulb are calculated as bright and the farther away ones are calculated as darker.

    */
    const int divisionsX = 20;
    const int divisionsZ = 20;

    float stepX = width / divisionsX;
    float stepZ = length / divisionsZ;
    

    /* If no texture is desired */
    if (texture == 0) {
        glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
        for (int x = 0; x < divisionsX; x++) {
            for (int z = 0; z < divisionsZ; z++) {

                float x1 = -halfWidth + x * stepX;
                float x2 = x1 + stepX;

                // For each x we get a range from x1 to x2 and inside this range we create 20 tiny rectangles with 20 different values of z1 and z2
                float z1 = -halfLength + z * stepZ;
                float z2 = z1 + stepZ;

                // Top face (y = -1.0f)
                glNormal3f(0.0f, 1.0f, 0.0f);
                                // Top face (y = -1.0f)
                glVertex3f(x1, top, z1);
                glVertex3f(x1, top, z2);
                glVertex3f(x2, top, z2);
                glVertex3f(x2, top, z1);

            }
        }
            
        // Bottom face (y = -1.0f)
        //glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glNormal3d(0.0f, -1.0f, 0.0f);
        glVertex3f(-halfWidth, -top, -halfLength);
        glVertex3f(halfWidth, -top, -halfLength);
        glVertex3f(halfWidth, -top, halfLength);
        glVertex3f(-halfWidth, -top, halfLength);

        // Front face  (z = 1.0f)
        //glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glNormal3d(0.0f, 0.0f, 1.0f);
        glVertex3f(halfWidth, top, halfLength);
        glVertex3f(-halfWidth, top, halfLength);
        glVertex3f(-halfWidth, -top, halfLength);
        glVertex3f(halfWidth, -top, halfLength);

        // Back face (z = -1.0f)
        //glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glNormal3d(0.0f, 0.0f, -1.0f);
        glVertex3f(halfWidth, -top, -halfLength);
        glVertex3f(-halfWidth, -top, -halfLength);
        glVertex3f(-halfWidth, top, -halfLength);
        glVertex3f(halfWidth, top, -halfLength);

        // Left face (x = -1.0f)
        //glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glNormal3d(-1.0f, 0.0f, 0.0f);
        glVertex3f(-halfWidth, top, halfLength);
        glVertex3f(-halfWidth, top, -halfLength);
        glVertex3f(-halfWidth, -top, -halfLength);
        glVertex3f(-halfWidth, -top, halfLength);

        // Right face (x = 1.0f)
    /*        glColor3f(r, g, b);   */
        glNormal3d(1.0f, 0.0f, 0.0f);
        glVertex3f(halfWidth, top, -halfLength);
        glVertex3f(halfWidth, top, halfLength);
        glVertex3f(halfWidth, -top, halfLength);
        glVertex3f(halfWidth, -top, -halfLength);
        glEnd();
    }
    else { // With texture
        glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        for (int x = 0; x < divisionsX; x++) {
            for (int z = 0; z < divisionsZ; z++) {

                float x1 = -halfWidth + x * stepX;
                float x2 = x1 + stepX;

                // For each x we get a range from x1 to x2 and inside this range we create 20 tiny rectangles with 20 different values of z1 and z2
                float z1 = -halfLength + z * stepZ;
                float z2 = z1 + stepZ;


                glNormal3f(0.0f, 1.0f, 0.0f);

                // Top face (y = -1.0f)
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(x1, top, z1);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(x1, top, z2);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(x2, top, z2);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(x2, top, z1);

            }
        }
        // Bottom face (y = -1.0f)
        //glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glNormal3d(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-halfWidth, -top, -halfLength);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(halfWidth, -top, -halfLength);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(halfWidth, -top, halfLength);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-halfWidth, -top, halfLength);

        // Front face  (z = 1.0f)
        //glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glNormal3d(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(halfWidth, top, halfLength);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-halfWidth, top, halfLength);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-halfWidth, -top, halfLength);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(halfWidth, -top, halfLength);

        // Back face (z = -1.0f)
        //glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glNormal3d(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(halfWidth, -top, -halfLength);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-halfWidth, -top, -halfLength);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-halfWidth, top, -halfLength);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(halfWidth, top, -halfLength);

        // Left face (x = -1.0f)
        //glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glNormal3d(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-halfWidth, top, halfLength);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-halfWidth, top, -halfLength);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-halfWidth, -top, -halfLength);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-halfWidth, -top, halfLength);

        // Right face (x = 1.0f)
    /*        glColor3f(r, g, b);   */
        glNormal3d(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(halfWidth, top, -halfLength);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(halfWidth, top, halfLength);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(halfWidth, -top, halfLength);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(halfWidth, -top, -halfLength);
        glEnd();
    }
    
}

void Pyramid::drawPyramid(float width, float length, float height, GLubyte r, GLubyte g, GLubyte b) {

    float halfWidth = width / 2;
    float halfLength = length / 2;
    float top = height / 2;

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
        // Front
        glColor3ub(r, g, b);
        glNormal3d(0.0f, top, 2*halfLength); // N = (B-A) X (C-A)
        glVertex3f(0.0f, halfLength, 0.0f); // A
        glVertex3f(-halfWidth, -halfLength, top); // B
        glVertex3f(halfWidth, -halfLength, top); // C

        // Right
        glNormal3d(2*halfLength, halfWidth, 0);
        glVertex3f(0.0f, halfLength, 0.0f);
        glVertex3f(halfWidth, -halfLength, top);
        glVertex3f(halfWidth, -halfLength, -top);

        // Back
        glNormal3d(0, top, -2*halfLength);
        glVertex3f(0.0f, halfLength, 0.0f);
        glVertex3f(halfWidth, -halfLength, -top);
        glVertex3f(-halfWidth, -halfLength, -top);

        // Left
        glNormal3d(-2*halfLength, halfWidth, 0);
        glVertex3f(0.0f, halfLength, 0.0f);
        glVertex3f(-halfWidth, -halfLength, -top);
        glVertex3f(-halfWidth, -halfLength, top);
    glEnd();   // Done drawing the pyramid
}