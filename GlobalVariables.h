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

/* Bulb: */
extern bool lightOn;
extern GLfloat jointRotationUnit;

/* Books */
extern GLfloat bookMovementDegree;
