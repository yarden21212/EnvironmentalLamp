#pragma once

#include <iostream>
#include <GL/freeglut.h>
#include "CommonLibraries.h"

#include "Menu.h"
#include "GlobalVariables.h"
#include "Shapes.h"
#include "Materials.h"

#define PI 3.1415927

// Camera's position
double cameraX = -2.6f, cameraY = 1.3f, cameraZ = -0.2f;
// Look-At target (where the camera is facing)
double targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;
// Up Vector (which way is "up")
double upX = 0.0f, upY = 1.0f, upZ = 0.0f;

/* Clipping window limits */
double xwMin = -1.0f, ywMin = -1.0f, xwMax = 1.0f, ywMax = 1.0f;
/* Near, Far planes */
double nearPlane = 1.0f, farPlane = 30.0f;


int windowW = 800;
int windowH = 800;

char title[] = "3D Table Lamp";

/* - - - - - - - - - - - - - Shapes - - - - - - - - - - - - */
GLfloat tableHeight = 0.6f;
GLfloat baseHeight = 0.1f;
GLfloat lowerBodyHeight = 2;
GLfloat connectorHeight = 0.2f;
GLfloat upperBodyHeight = 2;
GLfloat bottomConnectorHeight = 0.5f;
GLfloat armHeight = 0.2f;
GLfloat topHingeHeight = 0.03f;


/* Objects initialization*/
Cubes cube;
Cylinders cylinder;
Rectangles rectangle;
Pyramid pyramid;
MaterialType material;

/* Operation variables */
GLfloat rotateDegreeMain = 0;
GLfloat rotateDegreeSecond = 0;
GLfloat rotateDegreeTopHinge = 0;

/* Colors */
GLfloat silverColor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
GLfloat goldColor[] = { 0.83f, 0.69f, 0.22f, 1.0f };
GLfloat copperColor[] = { 0.95f, 0.64f, 0.54f, 1.0f };
GLfloat bronzeColor[] = { 0.80f, 0.50f, 0.20f, 1.0f };
GLfloat red[] = { 1.0f,0.0f,0.0f,1.0f };
GLfloat blueColor[] = { 0.27f, 0.51f, 0.71f, 1.0f };
GLfloat whiteColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat greenColor[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat yellowColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };


/* Materials */
GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat whiteSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat emission[] = { 1.0f, 1.0f, 0.5f, 1.0f };
GLfloat bulbEmission[] = { 1.0f, 1.0f, 0.7f, 1.0f };

/* Camera */
GLfloat cameraRotationUnit = 0.01f;
/* Light */
GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
int lightPower = 0;
GLfloat bulbPower = 1.0f;
GLfloat bulbLight[] = { bulbPower, bulbPower, bulbPower, 1.0f };
/* Bulb: */
GLfloat bulbColor[] = { 1.0f, 1.0f, 0.93f, 1.0f };
GLfloat bulbPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
bool lightOn = false;
GLfloat jointRotationUnit = 1.0f;

/* Books */
GLfloat bookMovement = 0.03f;
GLfloat bookMovementDegree = 30.0f;
GLfloat bookOpeningSpeed = 0.01f;


/* Menu */
GlutMenu gMenu;