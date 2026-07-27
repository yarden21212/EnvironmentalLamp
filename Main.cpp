/* 
    Sources I learned from:
    - Basics from the book
    - Lighting from https://math.hws.edu/graphicsbook/c4/s2.html and from https://www.cse.msu.edu/~cse872/tutorial3.html
*/

#include <iostream>
#include <GL/freeglut.h>
#include "CommonLibraries.h"

#include "Shapes.h"

#define PI 3.1415927

int windowW = 800;
int windowH = 800;

// Camera's position
double cameraX = -1.3f, cameraY = 0.5f, cameraZ = 2.5f;
// Look-At target (where the camera is facing)
double targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;
// Up Vector (which way is "up")
double upX = 0.0f, upY = 1.0f, upZ = 0.0f;

/* Clipping window limits */
double xwMin = -1.0f, ywMin = -1.0f, xwMax = 1.0f, ywMax = 1.0f;
/* Near, Far planes */
double nearPlane = 1.0f, farPlane = 30.0f;


char title[] = "3D Table Lamp";


/* - - - - - - - - - - - - - Shapes - - - - - - - - - - - - */
double tableHeight = 0.6;
double baseHeight = 0.1;
double lowerBodyHeight = 2;
double connectorHeight = 0.2;
double upperBodyHeight = 2;
double bottomConnectorHeight = 0.5;
double armHeight = 0.2;
double topHingeHeight = 0.03f;


/* Objects initialization*/
Cubes cube;
Cylinders cylinder;
Rectangles rectangle;
Pyramid pyramid;

/* Operation variables */
double rotateDegreeMain = 0;
double rotateDegreeSecond = 0;


/* Materials */
GLfloat red[] = { 1.0f,0.0f,0.0f,1.0f };
GLfloat specular[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat whiteSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat emission[] = {1.0f, 1.0f, 0.5f, 1.0f};
GLfloat bulbEmission[] = {1.0f, 1.0f, 0.7f, 1.0f};
GLfloat bulbLight[]  = {1.0f, 1.0f, 0.0f, 1.0f};

/* Light attributes */
float noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
/* Bulb attributes: */
float bulbColor[] = { 1.0f, 1.0f , 0.93f , 1.0f };
GLfloat bulbPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling

    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    glEnable(GL_NORMALIZE); // convert every normal to a unit-normal. (For every glNormal3d(x, y, z); it does calculation and converts to a unit-vector)

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();                 // Reset the model-view matrix

    // Camera transformation
    gluLookAt(cameraX, cameraY, cameraZ,       // Camera position
        targetX, targetY, targetZ,  // Look-at target
        upX, upY, upZ);
    glPushMatrix();


    /* Table */
    rectangle.drawRectangle(4.0, 2.6, tableHeight, 0, 0, 0.5);

    glTranslatef(-1.3f, tableHeight / 2.0f, 0.8f);  // Move right and into the screen
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    /* Lamp's base */
    cylinder.drawCylinder(0.3, baseHeight, 210, 210, 215);
    /* Small screw decoration for the connector*/
    glTranslatef(0.0f, 0.0f, baseHeight * 1.05);
    cylinder.drawCylinder(0.05, baseHeight, 168, 169, 173);

    /* Pyramid connector for the arms */
    glTranslatef(0.0f, 0.0f, baseHeight);
    glPushMatrix();
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    pyramid.drawPyramid(0.2, baseHeight *2, 0.2, 140, 140, 145);
    glPopMatrix();

    /* Lamp's arms*/
    glTranslatef(0.0f, 0.0f, baseHeight/2.5);
    const double armRadius = 0.03;
    const double armOffset = 0.05;
    glPushMatrix();

    glTranslatef(-armOffset, -0.1f, 0.0f);
    glRotatef(rotateDegreeMain, 1.0f, 0.0f, 0.0f);
    /* First arm */
    cylinder.drawCylinder(armRadius, armHeight, 210, 210, 215);
    glPushMatrix();

    /* Second arm */
    glTranslatef(2*armOffset, 0.0f, 0.0f);
    cylinder.drawCylinder(armRadius, armHeight, 250, 0, 0);
    glPopMatrix();

    /* Lamp's arms' connector */
    glTranslatef(0.0f, 0.0f, armHeight);
    glPushMatrix();
    glTranslatef(armOffset, 0.0f, 0.0f);
    cylinder.drawCylinder(0.1, baseHeight / 2, 210, 210, 215);
    glPopMatrix();

    /* Top arms */
    glTranslatef(0.0f, 0.0f, baseHeight / 2);

    glRotatef(-10.0f + rotateDegreeSecond, 1.0f, 0.0f, 0.0f);
    /* First arm */
    cylinder.drawCylinder(armRadius, armHeight, 210, 210, 215);
    glPushMatrix();

    /* Second arm */
    glTranslatef(2 * armOffset, 0.0f, 0.0f);
    cylinder.drawCylinder(armRadius, armHeight, 250, 0, 0);
    glPopMatrix();

    /* Lamp's arms' connector */
    glTranslatef(0.0f, 0.0f, armHeight);
    glPushMatrix();
    glTranslatef(armOffset, 0.0f, 0.0f);
    cylinder.drawCylinder(0.08f, baseHeight / 2, 210, 210, 215);
    glPopMatrix();

    /* Top hinge */
    glTranslatef(0.0f, 0.0f, baseHeight / 2);
    glTranslatef(armOffset, 0.0f, 0.0f);
    cylinder.drawCylinder(0.06f, topHingeHeight, 140, 140, 145);
    glPushMatrix();

    
    /* The bulb's cover (housing)*/
    glTranslatef(0.0f, 0.0f, 0.025);
    cylinder.drawCylinder(0.048f, 0.15f, 140, 140, 145);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.4);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.1f, 0.4, 20, 20);
    glPopMatrix();




    /*Bulb connector*/  
    glTranslatef(0.0f, 0.0f, 0.125);
    cylinder.drawCylinder(0.03f, 0.15, 0, 0, 0);
    glPushMatrix();
    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE,
        bulbLight
    );

    /* Bulb */
    glTranslatef(0.0f, 0.0f, 0.25f);
    //Light:
    glLightfv(GL_LIGHT0, GL_POSITION, bulbPos);
    glMaterialfv(GL_FRONT, GL_EMISSION, bulbColor);
    glutSolidSphere(0.05, 20, 20);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmission);

    glPopMatrix(); // upper-arm origin
    glPopMatrix(); // common arm origin
    glPopMatrix(); // whole lamp matrix

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        cameraY += 0.1;
    }
    else if (key == GLUT_KEY_DOWN) {
        cameraY -= 0.1;
    }
    else if (key == GLUT_KEY_RIGHT) {
        cameraX += 0.1;
    }
    else if (key == GLUT_KEY_LEFT) {
        cameraX -= 0.1;
    }
    else if (key == GLUT_KEY_F8) {
        cameraZ += 0.1;
    }
    else if (key == GLUT_KEY_F9) {
        cameraZ -= 0.1;
    }
    else if (key == GLUT_KEY_F1) {
        rotateDegreeMain += 1;
    }
    else if (key == GLUT_KEY_F2) {
        rotateDegreeMain -= 1;
    }
    else if (key == GLUT_KEY_F3) {
        rotateDegreeSecond += 1;
    }
    else if (key == GLUT_KEY_F4) {
        rotateDegreeSecond -= 1;
    }
    //else if (key == GLUT_KEY_CTRL_R) {
    //    rotateDegree -= 1;
    //}
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
    initGL();                       // Our own OpenGL initialization
    //glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}