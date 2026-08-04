/* 
    Sources I learned from:
    - Basics from the book
    - Lighting from https://math.hws.edu/graphicsbook/c4/s2.html, https://www.cse.msu.edu/~cse872/tutorial3.html
    - How to draw cylinder from https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6
    - How to work with the mouse - used documentations 7.4 - 7.6: https://www.opengl.org/resources/libraries/glut/spec3/node49.html 
    - How to create pop-up menu (used charGPT for completing itm because it missed few explanations): https://stackoverflow.com/questions/14370/glut-pop-up-menus + https://www.opengl.org/resources/libraries/glut/spec3/node37.html#SECTION00072000000000000000
*/

/* For image reading */
#include <iostream>
#include <iomanip>
#include <fstream>
/* End of image libraries */

#include "Main.h"
#include "Texture.h"


bool direction = false; // movement -> down
GLfloat rotateStartingValue = 0.0f;
void menuCallback(int item)
{
    gMenu.menu(item);
}

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.16f, 0.20f, 0.32f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling

    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    glEnable(GL_NORMALIZE); // convert every normal to a unit-normal. (For every glNormal3d(x, y, z); it does calculation and converts to a unit-vector)

    /* Global Lighting Properties */
    float ambientLevel[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLevel);

    // Enable lighting
    glEnable(GL_LIGHTING);
    /* LIGHT0 */
    glLightfv(GL_LIGHT0, GL_DIFFUSE, bulbLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, bulbLight);
    /* LIGHT1 */
    glLightfv(GL_LIGHT1, GL_DIFFUSE, sunLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, redColor);
    /* LIGHT2 */
    glLightfv(GL_LIGHT2, GL_DIFFUSE, bulbLight);
    glLightfv(GL_LIGHT2, GL_SPECULAR, redColor);
}


void generateBook(float color[]) {
    material.plastic("frontBack", redColor);
    rectangle.drawRectangle(0.3, 0.2, 0.01, 0.0f, 0.0f, 1.0f, 0);
    material.noMaterial();

    for (int i = 0; i < 10; i++) {
        glTranslatef(0.0f, -0.01f, 0.0f);
        if (i == 9) {
            material.plastic("frontBack", color);
        }
        else
        {
            material.plastic("frontBack", whiteColor);
        }
        rectangle.drawRectangle(0.3f, 0.2f, 0.01f, 0, 0, 0, 0);
        material.noMaterial();
    }
}

/* --------------------------- MOUSE -------------------------*/
void mouse(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN)
        return;

    if (button == 3)
    {
        // Wheel scrolled up
        cameraY += 0.1;
    }
    else if (button == 4)
    {
        // Wheel scrolled down
        cameraY -= 0.1;
    }

    /* Camera Movement */
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lightOn = !lightOn;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        //if (state == GLUT_DOWN) {
        //    lightOn = false;
        //}
    }

    glutPostRedisplay(); // Request a redraw to update the camera
}

/* Control the power of the bulb's light (3 different light powers) */
void controlLightPower() {
    lightPower = (lightPower + 1) % 2;  // Now in use right now, but seems like an options for future if I want to display the current power
    bulbPower -= (1.0f / 3.0f);         // The bulb has 3 powers 1/3, 2/3 and 1 which is defined as glMaterialfv(GL_FRONT, GL_EMISSION, bulbColor);  -> the closer to value 0,0,0, the more faded the light is
    bulbPower = bulbPower > 0 ? bulbPower : 1.0f;
    bulbLight[0] = bulbPower;
    bulbLight[1] = bulbPower;
    bulbLight[2] = bulbPower;
    bulbLight[3] = 1.0f;

    std::cout << bulbLight[0] << bulbLight[1] << bulbLight[2] << bulbLight[3] << std::endl;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, bulbLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, bulbLight);

}
GLuint texture = 0;

void generateStars() {
    glPushMatrix();
    material.plastic("frontBack", redColor);
    glEnable(GL_LIGHT2);
    material.noMaterial();


    glutPostRedisplay(); // Request a redraw to update the camera
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();                 // Reset the model-view matrix

    // Camera transformation
    gluLookAt(cameraX, cameraY, cameraZ,       // Camera position
        targetX, targetY, targetZ,  // Look-at target
        upX, upY, upZ);

    try {
        glPushMatrix();
        material.plastic("frontBack", redColor);
        skies.generateSun();
        material.noMaterial();
        glPopMatrix();


        glPushMatrix();
        /* Texture reading*/
        texture = LoadTexture("images/wooden-texture.bmp");
        /*end of image reading*/
        /* Texture binding */
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        /* Table */
        material.metal("frontBack", whiteColor);
        rectangle.drawRectangle(4.0, 2.6, tableHeight, 0, 0, 0.5, texture);
        glDisable(GL_TEXTURE_2D);

        glTranslatef(-1.3f, tableHeight / 2.0f, 0.8f);  // Move right and into the screen
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        material.noMaterial();

        /* Lamp's base */
        material.metal("frontBack", copperColor);
        cylinder.drawCylinder(0.3f, baseHeight, 210, 210, 215);
        /* Small screw decoration for the connector*/
        glTranslatef(0.0f, 0.0f, baseHeight * 1.05f);
        cylinder.drawCylinder(0.05f, baseHeight, 168, 169, 173);
        material.noMaterial();

        /* Pyramid connector for the arms */
        glTranslatef(0.0f, 0.0f, baseHeight);
        glPushMatrix();
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
        pyramid.drawPyramid(0.2, baseHeight * 2, 0.2f, 140, 140, 145);
        glPopMatrix();

        /* Lamp's arms*/
        material.metal("frontBack", silverColor);
        glTranslatef(0.0f, 0.0f, baseHeight / 2.5f);
        const GLfloat armRadius = 0.03f;
        const GLfloat armOffset = 0.05f;
        glPushMatrix();

        glTranslatef(-armOffset, -0.1f, 0.0f);
        glRotatef(rotateDegreeMain, 1.0f, 0.0f, 0.0f);
        /* First arm */
        cylinder.drawCylinder(armRadius, armHeight, 210, 210, 215);
        glPushMatrix();

        /* Second arm */
        glTranslatef(2 * armOffset, 0.0f, 0.0f);
        cylinder.drawCylinder(armRadius, armHeight, 250, 0, 0);
        material.noMaterial();
        glPopMatrix();


        /* Lamp's arms' connector */
        glTranslatef(0.0f, 0.0f, armHeight);
        glPushMatrix();
        glTranslatef(armOffset, 0.0f, 0.0f);
        material.metal("frontBack", copperColor);
        cylinder.drawCylinder(0.1f, baseHeight / 2, 210, 210, 215);
        glPopMatrix();
        material.noMaterial();

        /* Top arms */
        glTranslatef(0.0f, 0.0f, baseHeight / 2);

        glRotatef(-10.0f + rotateDegreeSecond, 1.0f, 0.0f, 0.0f);
        /* First arm */
        material.metal("frontBack", silverColor);
        cylinder.drawCylinder(armRadius, armHeight, 210, 210, 215);
        glPushMatrix();

        /* Second arm */
        glTranslatef(2 * armOffset, 0.0f, 0.0f);
        cylinder.drawCylinder(armRadius, armHeight, 250, 0, 0);
        glPopMatrix();
        material.noMaterial();

        /* Lamp's arms' connector */
        material.metal("frontBack", copperColor);
        glTranslatef(0.0f, 0.0f, armHeight);
        glPushMatrix();
        glTranslatef(armOffset, 0.0f, 0.0f);
        cylinder.drawCylinder(0.08f, baseHeight / 2, 210, 210, 215);
        glPopMatrix();
        material.noMaterial();

        /* Top hinge */
        material.metal("frontBack", blueColor);
        glTranslatef(0.0f, 0.0f, baseHeight / 2);
        glTranslatef(armOffset, 0.0f, 0.0f);
        /*test*/
        glRotatef(rotateDegreeTopHinge, 1.0f, 0.0f, 0.0f);
        /*test*/
        cylinder.drawCylinder(0.06f, topHingeHeight, 140, 140, 145);
        glPushMatrix();
        material.noMaterial();

        /* The bulb's cover (housing)*/
        glTranslatef(0.0f, 0.0f, 0.025f);
        material.metal("frontBack", blueColor);
        cylinder.drawCylinder(0.048f, 0.15f, 140, 140, 145);
        material.noMaterial();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.4f);
        glRotatef(180, 1.0f, 0.0f, 0.0f);
        material.metal("frontBack", copperColor);
        glutSolidCone(0.1f, 0.4, 20, 20);
        material.noMaterial();
        glPopMatrix();



        /*Bulb connector*/
        glTranslatef(0.0f, 0.0f, 0.125);
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bulbLight);
        cylinder.drawCylinder(0.03f, 0.15f, 0, 0, 0);
        float noAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, noAmbient);

        /* Bulb */
        glTranslatef(0.0f, 0.0f, 0.25f);
        //Light:
        if (lightOn) {
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, bulbPos);
            glMaterialfv(GL_FRONT, GL_EMISSION, bulbColor);
            glutSolidSphere(0.05, 20, 20);
            glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
        }
        else {
            glDisable(GL_LIGHT0);
            glutSolidSphere(0.05, 20, 20);
        }


        glPopMatrix(); // upper-arm origin
        glPopMatrix(); // common arm origin

        glTranslatef(-0.2f, 0.9f, -0.235f);
        glPushMatrix();
        /* normal Books */
        glTranslatef(0.0f, 0.8f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        generateBook(yellowColor);
        glTranslatef(0.0f, 0.0f, 0.01f);
        generateBook(greenColor);
        glTranslatef(0.0f, 0.0f, 0.01f);
        generateBook(blueColor);
        glPopMatrix();


        /* Interactive  book */
        glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
       
        material.plastic("frontBack", redColor);
        rectangle.drawRectangle(0.3, 0.2, 0.01, 0.0f, 0.0f, 1.0f, 0);
        material.noMaterial();

        for (int i = 0; i < 10; i++) {
            glTranslatef(0.0f, -0.01f, 0.0f);
            if (i == 9) {
                /* glTranslatef(0.0f, -0.1f, 0.1f);
                   glRotatef(-90, 1.0f, 0.0f, 0.0f);
                */
                glTranslatef(0.0f, -bookMovement, bookMovement);
                glRotatef(-bookMovementDegree, 1.0f, 0.0f, 0.0f);
                material.plastic("frontBack", redColor);
            }
            else
            {

                material.plastic("frontBack", whiteColor);
            }
            rectangle.drawRectangle(0.3f, 0.2f, 0.01f, 0, 0, 0, texture);
            material.noMaterial();
        }
        glPopMatrix();


        glPushMatrix();
        glTranslatef(2.0f, 0.8f, 0.2f);
        /* Teapot & cups */
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        material.metal("frontBack", bronzeColor);
        glutSolidTeapot(0.2);
        material.noMaterial();

        glTranslatef(0.5f, 0.0f, -0.1f);
        material.plastic("frontBack", whiteColor);
        glutSolidTeacup(0.2);
        glTranslatef(0.0f, 0.0f, 0.4f);
        glutSolidTeacup(0.2);
        material.noMaterial();
        glPopMatrix();


        glTranslatef(0.8f, 0.8f, 0.0f);
        /* PC's screen */
        glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        rectangle.drawRectangle(0.3f, 0.2f, 0.01f, 0.0f, 0.0f, 1.0f, 0);
        glTranslatef(0.0f, 0.0f, 0.01f);
        rectangle.drawRectangle(0.15f, 0.14f, 0.22f, 0.0f, 0.0f, 1.0f, 0);
        glTranslatef(0.0f, -0.4f, 0.0f);
        float blackColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        material.metal("frontBack", blackColor);
        rectangle.drawRectangle(0.8f, 0.05, 0.6f, 0.0f, 0.0f, 1.0f, 0);
        material.noMaterial();
        glPopMatrix();

        glPopMatrix();
        glPopMatrix(); // whole lamp matrix or whote table matrix (I'm not sure)


    }
    catch (std::invalid_argument e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        cameraX += 10 * cameraRotationUnit;
    }
    else if (key == GLUT_KEY_DOWN) {
        cameraX -= 10 * cameraRotationUnit;
    }
    else if (key == GLUT_KEY_RIGHT) {
        cameraZ += 10*cameraRotationUnit;
    }
    else if (key == GLUT_KEY_LEFT) {
        cameraZ -= 10 * cameraRotationUnit;
    }
    else if (key == GLUT_KEY_F1) {
        rotateDegreeMain += jointRotationUnit;
    }
    else if (key == GLUT_KEY_F2) {
        rotateDegreeMain -= jointRotationUnit;
    }
    else if (key == GLUT_KEY_F3) {
        rotateDegreeSecond += jointRotationUnit;
    }
    else if (key == GLUT_KEY_F4) {
        rotateDegreeSecond -= jointRotationUnit;
    }
    else if (key == GLUT_KEY_F5) {
        controlLightPower();
    }
    else if (key == GLUT_KEY_SHIFT_L) {
        if(bookMovement < 1 && bookMovementDegree < 90)
        {
            bookMovement += 0.01f;
            bookMovementDegree += 10;
        }
    }
    else if (key == GLUT_KEY_SHIFT_R) {
        if (bookMovement > 0 && bookMovementDegree > 0)
        {
            bookMovement -= 0.01f;
            bookMovementDegree -= 10;
        }
    }
    else if (key == GLUT_KEY_F8) {
        if (rotateDegreeTopHinge >= -50)
        {
            rotateDegreeTopHinge -= 1;
            std::cout << "top hinge: " << rotateDegreeTopHinge << std::endl;
        }
    }
    else if (key == GLUT_KEY_F9) {
        if (rotateDegreeTopHinge < 0)
        {
            rotateDegreeTopHinge += 1;
            std::cout << "top hinge: " << rotateDegreeTopHinge << std::endl;
        }
    }


    glutPostRedisplay(); // Request a redraw to update the camera
}
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   glFrustum(-aspect, aspect, ywMin, ywMax, nearPlane, farPlane);

   glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);

    /* Glut menu: */
    // Create a menu
    glutCreateMenu(menuCallback);
    // Add menu items
    glutAddMenuEntry("Reset scene (Press here!) ", GlutMenu::MENU_FIRST);
    glutAddMenuEntry("SHIFT R+L to Open/Close the red book ", GlutMenu::MENU_SECOND);
    glutAddMenuEntry("F1-F4 to control the bulb's joints (to move it)", GlutMenu::MENU_THIRD);
    glutAddMenuEntry("Mouse-Wheel & Arrow Keys to control the camera ", GlutMenu::MENU_FOURTH);
    glutAddMenuEntry("Left mouse to turn on/off the bulb ", GlutMenu::MENU_FIFTH);
    glutAddMenuEntry("F5 to control the light's power", GlutMenu::MENU_SIXTH);
    glutAddMenuEntry("F8 to control the bulb's top joint ", GlutMenu::MENU_SEVENTH);
    glutAddMenuEntry("Thanks for using my program!! ", GlutMenu::MENU_EIGHTH);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}


