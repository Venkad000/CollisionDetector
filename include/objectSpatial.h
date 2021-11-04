#ifndef OBJECTSPATIAL_H
#define OBJECTSPATIAL_H

#include "cellSpatial.h"
#include "vector.h"

namespace Spatial{

    class objectSpatial{
        public:
            virtual ~objectSpatial() {}
        
        public:
            virtual int checkCollision( objectSpatial* object)  = 0;

            virtual void collisionOn() = 0;
            virtual void collisionOff() = 0;
            virtual int getCollisionStatus()  = 0;

            virtual void setPosition(Vector& refPosition) = 0;
            virtual  Vector& getPosition()  = 0;

            virtual void setDirection(Vector& refDirection) = 0;
            virtual  Vector& getDirection()  = 0;

            virtual void setRadius(float radius) = 0;
            virtual float getRadius() = 0;

            virtual int getId()  = 0;

            virtual void setCell(cellSpatial* pCell) = 0;
            virtual cellSpatial* getCell() = 0;

            virtual objectSpatial* getNext() = 0;
            virtual void setNext(objectSpatial* pObject) = 0;

            virtual void setLevel(int Level) = 0;
            virtual int getLevel()  = 0;

    };
} 

#endif 
