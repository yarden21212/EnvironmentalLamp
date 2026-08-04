#pragma once
// Camera's position
extern double cameraX, cameraY, cameraZ;
// Look-At target (where the camera is facing)
extern double targetX, targetY, targetZ;
// Up Vector (which way is "up")
extern double upX, upY, upZ;

/* Clipping window limits */
extern double xwMin, ywMin, xwMax, ywMax;
/* Near, Far planes */
extern double nearPlane, farPlane;

/* Operation variables */
extern GLfloat rotateDegreeMain;
extern GLfloat rotateDegreeSecond;
extern GLfloat rotateDegreeTopHinge;

/* Colors */
extern GLfloat silverColor[];
extern GLfloat goldColor[];
extern GLfloat copperColor[];
extern GLfloat bronzeColor[];
extern GLfloat redColor[];
extern GLfloat blueColor[];
extern GLfloat whiteColor[];
extern GLfloat greenColor[];
extern GLfloat yellowColor[];


/* Materials */
extern GLfloat noEmission[];

/* Bulb: */
extern bool lightOn;
extern GLfloat jointRotationUnit;

/* Books */
extern GLfloat bookMovementDegree;

/* Sun */
extern GLfloat sunTableRadius;
extern GLfloat degree;
extern GLfloat sunPos[];

