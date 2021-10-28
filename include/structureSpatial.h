#ifndef STRUCTURESPATIAL_H
#define STRUCTURESPATIAL_H

#include "objectSpatial.h"
#include <vector>

namespace Spatial{
    class structreSpatial{
        public:
            virtual ~structreSpatial();
    
        public:
            virtual void addObjects(const std::vector<objectSpatial*>&refObjects) = 0;

            virtual void update() = 0;
    };
}

#endif