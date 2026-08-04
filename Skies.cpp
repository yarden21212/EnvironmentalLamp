/* This class is meant to create every object that belongs to the sky: sun, stars */
#include "Skies.h"


void SkiesObjects::generateSun() {

    // The sun will rotate around the x-axis, in order to move around the table in space
    degree += 0.0001f;
    GLfloat sunX = 0.0f;
    GLfloat sunY = sunTableRadius * cos(degree);
    GLfloat sunZ = sunTableRadius * sin(degree);
    GLfloat sunLoc[] = { sunX, sunY, sunZ };

    glEnable(GL_LIGHT1);
    glTranslatef(sunX, sunY, sunZ);  // Move right and into the screen
    glLightfv(GL_LIGHT1, GL_POSITION, sunLoc);
    glMaterialfv(GL_FRONT, GL_EMISSION, redColor);
    glutSolidSphere(2.0f, 30, 30);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glutPostRedisplay(); // Request a redraw to update the camera
}


/* Generates approximately 400 stars in order to create a calmed environment */
void SkiesObjects::generateStars(const int distance) {
    int randomDistance;

    GLfloat starsX = 0.0f;
    GLfloat starsY = 0.5f;
    GLfloat starsZ = distance;

    float starLoc[] = { starsX, starsY, starsZ };
    glEnable(GL_LIGHT2);


    for (int i = 0; i < starsCount; i++) {

        glTranslatef(starsX, starsY, stars[i]);  // Move right and into the screen
        glLightfv(GL_LIGHT2, GL_POSITION, starLoc);
        glMaterialfv(GL_FRONT, GL_EMISSION, whiteColor);
        glutSolidSphere(0.005f, 4, 4);
        glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    }




}