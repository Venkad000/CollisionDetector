#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "bruteforce.h"

#include "vector.h"
#include "points.h"

#include "objectSpatial.h"
#include "structureSpatial.h"
#include "sphere.h"

static Spatial::structureSpatial* pSpatialStructure = NULL;
static std::vector<Spatial::objectSpatial*> vectorOfObjects;

static float radiusMax = 1.25f;
static float radiusMin = 7.25f;

static int objectCount = 1000;

static int lastId = 0;
static float startOffset = 50.0f;

static Vector vectorMaximumValues = Vector(100,100,100);
static Vector vectorMinimumValues = Vector(-100,-100,-100);

static float frame = 0.015f;

static int screenWidth = 720;
static int screenBreadth = 1280;

static int lastx = 0;
static int lasty = 0;

static int rotationx = 0;
static int rotationy = 0;

static int firstFrame = 1;
static int frameCount = 0;

static int    timeBase = 0;
static float  fps = 0.0f;
static int    resetFps = 0;
static float  maxFps = 0.0f;

static int    currentSpatial = 2;
static int    drawBox = 1;
static int    drawAxis = 0;
static int    showCollisionCount = 1;
static int    maxCollisions = 0;
static int    currentRebuild = 0;
static int    pause = 0;
static int    oneFrame = 0;

static void printText(std::string& refString, int x, int y);
static void renderInfo();
static void renderScene();
static void setupRc();
static void changeSize(GLsizei w, GLsizei h);
static void mouseAction(int x, int y);
static void keyboard(unsigned char key, int x, int y);

static void createObjects();
static void deleteObjects();
static void createSpatialStructure();
static void deleteSpatialStructure();

static void tick();

static void createObjects(){

    float radius;

    Vector vectorPosition;
    Vector vectorDirection;

    Spatial::Sphere* pSphere;

    srand(time(0));

    for(int index = 0;index < objectCount;index++){
        radius = (rand() / (static_cast<float>(RAND_MAX) + 1.0f)) * (radiusMax - radiusMin) + radiusMin;

        vectorPosition.setX((rand() / (static_cast<float>(RAND_MAX)+ 1.0f) )*(radiusMax - radiusMin) + radiusMin);
        vectorPosition.setY((rand() / (static_cast<float>(RAND_MAX)+ 1.0f) )*(radiusMax - radiusMin) + radiusMin); 
        vectorPosition.setZ((rand() / (static_cast<float>(RAND_MAX)+ 1.0f) )*(radiusMax - radiusMin) + radiusMin); 
        
        vectorDirection.setX((rand() / (static_cast<float>(RAND_MAX)+ 1.0f) )*(radiusMax - radiusMin) + radiusMin); 
        vectorDirection.setY((rand() / (static_cast<float>(RAND_MAX)+ 1.0f) )*(radiusMax - radiusMin) + radiusMin); 
        vectorDirection.setZ((rand() / (static_cast<float>(RAND_MAX)+ 1.0f) )*(radiusMax - radiusMin) + radiusMin); 

        pSphere = new Spatial::Sphere(lastId);
        pSphere->setPosition(vectorPosition);
        pSphere->setDirection(vectorDirection);
        pSphere->setRadius(radius);

        vectorOfObjects.push_back(pSphere);
        ++lastId;

    }
}

static void deleteObjects(){
    std::vector<Spatial::objectSpatial*>::iterator iter_objects;

    for(iter_objects = vectorOfObjects.begin();iter_objects!=vectorOfObjects.end();iter_objects++){
        delete((*iter_objects));
        (*iter_objects) = NULL;
    }

}

static void createSpatialStructure(){
    switch(currentSpatial){
        case 1:
            delete(pSpatialStructure);
            pSpatialStructure = new Spatial::BruteForce();
            break;
        default:
            return;
    }

    resetFps = 1;
    maxCollisions = 0;
    pSpatialStructure->addObjects(vectorOfObjects);

}

static void deleteSpatialStructure(){
    delete(pSpatialStructure);
    pSpatialStructure = NULL;
}

static void tick(){
    float radius;
    int collision;

    Vector vectorPosition;
    Vector vectorDirection;
    Vector vectorNormal;

    if (oneFrame && pause){
        pause = 0;
    }

    if(!pause){
        std::vector<Spatial::objectSpatial*>::iterator iter_objects;
        for(iter_objects = vectorOfObjects.begin();iter_objects!=vectorOfObjects.end();iter_objects++){
            (*iter_objects)->collisionOff();
            vectorPosition = (*iter_objects)->getPosition();
            vectorDirection = (*iter_objects)->getDirection();
            radius = (*iter_objects)->getRadius();

            collision = 0;

            if(vectorPosition.getx() - radius <= vectorMinimumValues.getx()){
                vectorNormal = Vector(1.0f,0.0f,0.0f);
                vectorDirection -= 2.0f * vectorNormal * vectorDirection.dot(vectorNormal);
                (*iter_objects)->setDirection(vectorDirection);
                collision = 1;
            }

            if(vectorPosition.getx() + radius >= vectorMaximumValues.getx()){
                vectorNormal = Vector(-1.0f,0.0f,0.0f);
                vectorDirection -= 2.0f * vectorNormal * vectorDirection.dot(vectorNormal);
                (*iter_objects)->setDirection(vectorDirection);
                collision = 1;
            }

            if(vectorPosition.getz() - radius <= vectorMinimumValues.getz()){
                vectorNormal = Vector(0.0f,0.0f,1.0f);
                vectorDirection -= 2.0f * vectorNormal * vectorDirection.dot(vectorNormal);
                (*iter_objects)->setDirection(vectorDirection);
                collision = 1;
            }

            if(vectorPosition.getx() + radius >= vectorMaximumValues.getz()){
                vectorNormal = Vector(0.0f,0.0f,-1.0f);
                vectorDirection -= 2.0f * vectorNormal * vectorDirection.dot(vectorNormal);
                (*iter_objects)->setDirection(vectorDirection);
                collision = 1;
            }

            if(vectorPosition.gety() - radius <= vectorMinimumValues.getx()){
                vectorNormal = Vector(0.0f,1.0f,0.0f);
                vectorDirection -= 2.0f * vectorNormal * vectorDirection.dot(vectorNormal);
                (*iter_objects)->setDirection(vectorDirection);
                collision = 1;
            }

            if(vectorPosition.getx() - radius >= vectorMaximumValues.getx()){
                vectorNormal = Vector(0.0f,-1.0f,0.0f);
                vectorDirection -= 2.0f * vectorNormal * vectorDirection.dot(vectorNormal);
                (*iter_objects)->setDirection(vectorDirection);
                collision = 1;
            }

            if(!collision){
                vectorNormal = Vector(0.0f,0.0f,0.0f);
                vectorDirection -= 2.0f * vectorNormal * vectorDirection.dot(vectorNormal);
                (*iter_objects)->setDirection(vectorDirection);
            }

            vectorPosition += vectorDirection * frame;
            (*iter_objects)->setPosition(vectorPosition);

            if(oneFrame){
                pause = 1;
                oneFrame = 0;
            }


        }

        pSpatialStructure->update();

    }
    glutPostRedisplay();
}

static void printText(std::string& refString, int x, int y){
    glMatrixMode(GL_PROJECTION);    
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0,screenWidth,0,screenBreadth);
    glScalef(1,-1,1);
    glTranslatef(0,-screenBreadth,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos2f(x, y);
    
    for(int i = 0;i<refString.size();i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,refString[i]);
    }

    glColor3f(1.0f,0.0f,0.0f);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);


}   

static void renderInfo(){
    int time;
    int collisionCount;

    std::stringstream ssSerial;
    std::string sBuf;

    sBuf = "";
    ssSerial.str("");
    ssSerial << "[1] Brute Force    ";
    ssSerial << "[2] Sort and Sweep    ";
    ssSerial << "[3] Uniform Grid    ";
    ssSerial << "[4] Hierarchical Grid    ";
    ssSerial << "[5] Octree / Octree (Rebuild)   ";
    
    sBuf = ssSerial.str();
    printText(sBuf, 20, 20);
    
    
    
    // [rad] middle menu
    sBuf = "";
    ssSerial.str("");
    ssSerial << "[6] Loose Octree / Loose Octree (Rebuild)    ";
    ssSerial << "[7] KD-Tree (SAH)    ";
        
    sBuf = ssSerial.str();
    printText(sBuf, 20, 40);
    
    
    
    // [rad] Lower menu
    sBuf = "";
    ssSerial.str("");
    ssSerial << "[Q] Quit    ";
    ssSerial << "[B] Enable / Disable Box    ";
    ssSerial << "[X] Enable / Disable Axis    ";
    ssSerial << "[N] Show Collision Count    ";
    sBuf = ssSerial.str();
    printText(sBuf, 20, 70);
    
    
    // [rad] Lower menu (2nd)
    sBuf = "";
    ssSerial.str("");
    ssSerial << "[P] Pause    ";
    ssSerial << "[Space] One Frame (Pause)    "; 
    ssSerial << "[R] Reposition    ";
    sBuf = ssSerial.str();
    printText(sBuf, 20, 90);

    sBuf = "";
    ssSerial.str("");
    ssSerial << "Spatial Structure: ";
    
    switch(currentSpatial)
    {
        case 1:
            {
                ssSerial << "Brute force";
            }
            break;
            
        case 2:
            {
                ssSerial << "Sort and Sweep";
            }
            break;
            
        case 3:
            {
                ssSerial << "Uniform Grid";
            }
            break;
            
        case 4:
            {
                ssSerial << "Hierarchical Grid";
            }
            break;
            
        case 5:
            {
                if(!currentRebuild)
                {
                    ssSerial << "Octree";
                }
                else
                {
                    ssSerial << "Octree (Rebuild)";
                }
            }
            break;
            
        case 6:
            {
                if(!currentRebuild)
                {
                    ssSerial << "Loose Octree";
                }
                else
                {
                    ssSerial << "Loose Octree (Rebuild)";
                }
            }
            break;
            
            
        case 7:
            {
                ssSerial << "KD-Tree (SAH)";
            }
            break;
            
            
        default:
            ssSerial << "Unknown";
    }

    sBuf = ssSerial.str();
    printText(sBuf, 20, 130);

    ++frameCount;

    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timeBase > 1000){
        fps = frameCount*1000.0f/static_cast<float>(time-timeBase);
        timeBase = time;
        frameCount = 0;

        if (resetFps){
            resetFps = 0;
            maxFps = 0.0f;
            fps = 0.0f;
        }


    }

    if(maxFps < fps){
        maxFps = fps;
    }


    sBuf = "";
    ssSerial.str("");
    ssSerial << "FPS: " << fps;
    sBuf = ssSerial.str();
   
    printText(sBuf, 20, 150);
    
    
    sBuf = "";
    ssSerial.str("");
    ssSerial << "Maximum FPS: " << maxFps;
    sBuf = ssSerial.str();
   
    printText(sBuf, 20, 170);
    
    

    sBuf = "";
    ssSerial.str("");
    ssSerial << "Number of objects: " << objectCount;
    sBuf = ssSerial.str();
    
    printText(sBuf, 20, 190);
   
   
   
    // [rad] Calculate number of collisions
    std::vector<Spatial::objectSpatial*>::iterator iter_objects;
    for(iter_objects = vectorOfObjects.begin(); iter_objects != vectorOfObjects.end(); iter_objects++)
    {
        if((*iter_objects)->getCollisionStatus())
        {
            ++collisionCount;
        }
    }
    
    
    // [rad] Update collision count, if needed
    if(maxCollisions < collisionCount)
    {   
        maxCollisions = collisionCount;
    }
   
   
   
    // [rad] Print collision count
    if(showCollisionCount)
    {
        sBuf = "";
        ssSerial.str("");
    
        ssSerial << "Number of collisions: " << (collisionCount / 2);
        sBuf = ssSerial.str();
   
        printText(sBuf, 20, 210);
        
        
        sBuf = "";
        ssSerial.str("");
    
        ssSerial << "Maximum number of collisions: " << (collisionCount / 2);
        sBuf = ssSerial.str();
   
        printText(sBuf, 20, 230);
    }
}

static void renderScene()
{
    // [rad] Do object update / collision detection
    tick();

    
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // [rad] Render text
    renderInfo();
    
    
    // [rad] Rotate scene if necessary
    glRotatef(rotationx, 1.0f, 0.0f, 0.0f);
    rotationx = 0.0f;

    glRotatef(rotationy, 0.0f, 1.0f, 0.0f);
    rotationy = 0.0f;
    
    
    // [rad] Render all objects
    std::vector<Spatial::objectSpatial*>::iterator iter_objects;
    for(iter_objects = vectorOfObjects.begin(); iter_objects != vectorOfObjects.end(); iter_objects++)
    {
        glPushMatrix();
        glTranslatef((*iter_objects)->getPosition().getx(), (*iter_objects)->getPosition().gety(),
                        (*iter_objects)->getPosition().getz());
                        
        
        // [rad] Check if this object is colliding
        if((*iter_objects)->getCollisionStatus())
        {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        else
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        }
                        
                        
        // [rad] We'll use cubes to draw our spheres, since they require the
        // least number of polygons
        glutSolidCube((*iter_objects)->getRadius());
        
        glPopMatrix();
    }
    
    
    // [rad] Draw box (cube) if enabled
    if(drawBox)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        
        //glutWireCube(200.0f);
        
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(5, 0x55555);    
            
        
        glBegin(GL_LINE_STRIP);
        
            glVertex3f(-100.0f, 100.0f, -100.0f);
            glVertex3f(100.0f, 100.0f, -100.0f);
            glVertex3f(100.0f, 100.0f, 100.0f);
            glVertex3f(-100.0f, 100.0f, 100.0f);
            glVertex3f(-100.0f, 100.0f, -100.0f);
        
        glEnd();
        
        
        glBegin(GL_LINE_STRIP);
        
            glVertex3f(-100.0f, -100.0f, -100.0f);
            glVertex3f(100.0f, -100.0f, -100.0f);
            glVertex3f(100.0f, -100.0f, 100.0f);
            glVertex3f(-100.0f, -100.0f, 100.0f);
            glVertex3f(-100.0f, -100.0f, -100.0f);
        
        glEnd();
            
                    
        glBegin(GL_LINES);
        
            glVertex3f(-100.0f, 100.0f, 100.0f);
            glVertex3f(-100.0f, -100.0f, 100.0f);
            
            glVertex3f(-100.0f, 100.0f, -100.0f);
            glVertex3f(-100.0f, -100.0f, -100.0f);
            
            glVertex3f(100.0f, 100.0f, -100.0f);
            glVertex3f(100.0f, -100.0f, -100.0f);
            
            glVertex3f(100.0f, 100.0f, 100.0f);
            glVertex3f(100.0f, -100.0f, 100.0f);
        
        glEnd();
        
        
        glDisable(GL_LINE_STIPPLE);
    }
    
    
    // [rad] Draw axis
    if(drawAxis)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(5, 0x55555);

        
        glBegin(GL_LINES);

            glVertex3f(-150.0f, 0.0f, 0.0f);
            glVertex3f(150.0f, 0.0f, 0.0f);

            glVertex3f(0.0f, -150.0f, 0.0f);
            glVertex3f(0.0f, 150.0f, 0.0f);
            
            glVertex3f(0.0f, 0.0f, -150.0f);
            glVertex3f(0.0f, 0.0f, 150.0f);
    
        glEnd();
        
        
        glDisable(GL_LINE_STIPPLE);
    }
    
    
    // [rad] Swap double buffer
    glutSwapBuffers();
}


static void setupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}


static void shangeSize(GLsizei w, GLsizei h)
{
    // [rad] Store new size
    screenWidth = w;
    screenBreadth = h;
    
    
    GLfloat range = 200.0f;
    
    if(!h)
    {
        h = 1;
    }
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(w <= h)
    {
        glOrtho(-range, range, -range * h / w, range * h / w, -range, range);
    }
    else
    {
        glOrtho(-range * w / h, range * w /h, -range, range, -range, range);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void changeSize(GLsizei w, GLsizei h)
{
    // [rad] Store new size
    screenWidth = w;
    screenBreadth = h;
    
    
    GLfloat range = 200.0f;
    
    if(!h)
    {
        h = 1;
    }
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(w <= h)
    {
        glOrtho(-range, range, -range * h / w, range * h / w, -range, range);
    }
    else
    {
        glOrtho(-range * w / h, range * w /h, -range, range, -range, range);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void keyboard(unsigned char u8Key, int i32X, int i32Y)
{
    int i32Value = u8Key - 48;
    
    if(i32Value >= 1 && i32Value <= 7)
    {
        if(i32Value == currentSpatial)
        {
            currentRebuild = !currentRebuild;
        }
        else
        {
            currentSpatial = i32Value;
            currentRebuild = 0;
        }

        createSpatialStructure();
    }
    else if(u8Key == 'b' || u8Key == 'B')
    {
        drawBox = !drawBox;
    }
    else if(u8Key == 'x' || u8Key == 'X')
    {
        drawBox = !drawBox;
    }
    else if(u8Key == 'q' || u8Key == 'Q')
    {
        exit(0);
    }
    else if(u8Key == 'n' || u8Key == 'N')
    {
        showCollisionCount = !showCollisionCount;
    }
    else if(u8Key == 'r' || u8Key == 'R')
    {
        changeSize(screenWidth, screenBreadth);
    }
    else if(u8Key == 'p' || u8Key == 'P')
    {
        pause = !pause;
    }
    else if(u8Key == ' ')
    {
        if(!pause)
        {
            pause = 0;
        }
        
        oneFrame = 1;
    }
}


static void mouseAction(int i32X, int i32Y){
    if(firstFrame)
    {
        firstFrame = 0;
    }
    else
    {
        rotationx = static_cast<float>(lastx - i32X) * 0.5f;
        rotationy = static_cast<float>(lasty - i32Y) * 0.5f;
    }
    
    lastx = i32X;
    lasty = i32Y;
}


int main(int argc,char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth,screenBreadth);
    glutCreateWindow("Collision data structures");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutMotionFunc(mouseAction);
    glutKeyboardFunc(keyboard);

    createObjects();
    createSpatialStructure();

    setupRC();

    glutMainLoop();

    deleteSpatialStructure();
    deleteObjects();

    return(0);
}
