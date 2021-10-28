#ifndef OBJECTSPATIAL_H
#define OBJECTSPATIAL_H

#include "cellSpatial.h"
#include "vector.h"

namespace Spatial{

    class objectSpatial{
        public:
            virtual ~objectSpatial();
        
        public:
            virtual int checkCollision(const objectSpatial* object) const = 0;

            virtual void collisionOn() = 0;
            virtual void collisionOff() = 0;
            virtual void getCollisionStatus() const = 0;

            virtual void setPosition(Vector& refPosition) = 0;
            virtual const Vector& getPosition() const = 0;

            virtual void setDirection(Vector& refDirection) = 0;
            virtual const Vector& getDirection() const = 0;

            virtual int getId() const = 0;

            virtual void setCell(cellSpatial* pCell) = 0;
            virtual cellSpatial* getCell() = 0;

            virtual objectSpatial* getNext() = 0;
            virtual void setNext(objectSpatial* pObject) = 0;

            virtual void setLevel(int i32Level) = 0;
            virtual int getLevel() const = 0;

    };
} 

#endif 
