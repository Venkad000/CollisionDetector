#ifndef SPHERE_H
#define SPHERE_H

#include "objectSpatial.h"

namespace Spatial{
    
    class cellSpatial;

    class Sphere: public objectSpatial{
        public:
            Sphere(int i32Id);

            

            int checkCollision(objectSpatial* object);

            void setPosition(Vector& refVector);
            Vector& getPosition();

            void setDirection(Vector& refDirection);
            Vector& getDirection();

            void setRadius(float radius);
            float getRadius();

            int getId();
            
            void setCell(cellSpatial* cell);
            cellSpatial* getCell();

            void collisionOn();
            void collisionOff();
            int getCollisionStatus();

            objectSpatial* getNext();
            void setNext(objectSpatial* object);

            void setLevel(int level);
            int getLevel();

        protected:

            int Id;
            int collision;
            int level;
            int radius;

            Vector vectorPosition;
            Vector vectorDirection;

            cellSpatial* pcellSpatial;

            objectSpatial* nextObject;
    };
}


#endif