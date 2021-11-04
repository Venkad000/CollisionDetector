#include "base.h"

#include "sphere.h"

#include <iostream>
#include <cstdlib>

namespace Spatial{
    Sphere::Sphere(int Id):objectSpatial(),Id(Id),pcellSpatial(NULL),collision(0),nextObject(NULL),level(0){

    }

    void Sphere::setLevel(int level){
        this->level = level;
    }

    int Sphere::getLevel(){
        return level;
    }

    void Sphere::collisionOn(){
        collision = 1;
    }

    void Sphere::collisionOff(){
        collision = 0;
    }

    int Sphere::getCollisionStatus(){
        return collision;
    }

    int Sphere::checkCollision(objectSpatial* pObject){
        Vector tempVec = vectorPosition - pObject->getPosition();

        float distance = tempVec.dot(tempVec);
        float radiusSum = radius + pObject->getRadius();

        return distance <= radiusSum*radiusSum;
    }

    void Sphere::setPosition(Vector& refPosition){
        vectorPosition = refPosition;
    }

    Vector& Sphere::getPosition(){
        return vectorPosition;
    }

    void Sphere::setDirection(Vector& refDirection){
        vectorDirection = refDirection;
    }

    Vector& Sphere::getDirection(){
        return vectorDirection;
    }

    void Sphere::setRadius(float radius){
        radius = radius;
    }

    float Sphere::getRadius(){
        return radius;
    }

    int Sphere::getId(){
        return Id;
    }

    void Sphere::setCell(cellSpatial* pCell){
        pcellSpatial = pCell;
    }

    cellSpatial* Sphere::getCell(){
        return(pcellSpatial);
    }

    objectSpatial* Sphere::getNext(){
        return(nextObject);
    }

    void Sphere::setNext(objectSpatial* pObject){
        nextObject = pObject;
    }

}