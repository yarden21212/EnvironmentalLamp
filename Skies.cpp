#include "Skies.h"


void SkiesObjects::generateSun() {

    degree += 0.001f;
    GLfloat sunX = 0.0f;
    GLfloat sunY = sunTableRadius * cos(degree);
    GLfloat sunZ = sunTableRadius * sin(degree);
    GLfloat sunLoc[] = { sunX, sunY, sunZ };
    std::cout << sunLoc << std::endl;
    std::cout << sunX << sunX << 0.0f << std::endl;

    glEnable(GL_LIGHT1);
    glTranslatef(sunX, sunY, sunZ);  // Move right and into the screen
    glLightfv(GL_LIGHT1, GL_POSITION, sunLoc);
    glMaterialfv(GL_FRONT, GL_EMISSION, redColor);
    glutSolidSphere(2.0f, 20, 20);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glutPostRedisplay(); // Request a redraw to update the camera


}