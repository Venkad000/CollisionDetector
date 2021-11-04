#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "structureSpatial.h"
#include <vector>

namespace Spatial{
    class BruteForce: public structureSpatial{
        public:
            BruteForce();

            void addObjects(std::vector<objectSpatial*>& refObjects);
            void update();
        protected:
            std::vector<objectSpatial*> vectorOfObjects;
    };
}

#endif