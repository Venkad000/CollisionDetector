#ifndef STRUCTURESPATIAL_H
#define STRUCTURESPATIAL_H

#include "objectSpatial.h"
#include <vector>

namespace Spatial{
    class structureSpatial{
        public:
            virtual ~structureSpatial() {}
    
        public:
            virtual void addObjects( std::vector<objectSpatial*>&refObjects) = 0;

            virtual void update() = 0;
    };
}

#endif