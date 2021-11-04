#include "bruteforce.h"
#include <cstdlib>

namespace Spatial{
    BruteForce::BruteForce():structureSpatial(){

    }

    void BruteForce::addObjects(std::vector <objectSpatial*>&refObjects){
        std::vector<objectSpatial*>::const_iterator iter;
        for(iter = refObjects.begin();iter!=refObjects.end();iter++){
            vectorOfObjects.push_back(*iter);
        }
    }

    void BruteForce::update(){
        std::vector<objectSpatial*>::const_iterator iter1;
        std::vector<objectSpatial*>::const_iterator iter2;

    for(iter1 = vectorOfObjects.begin();iter1!=vectorOfObjects.end();iter1++){
        for(iter2 = vectorOfObjects.begin();iter2!=vectorOfObjects.end();iter2++){
            if ((*iter1)->getId() < (*iter2)->getId()){
                if ((*iter1)->checkCollision(*iter2)){
                    (*iter1)->collisionOn();
                    (*iter2)->collisionOn();
                }
            }
        }
    }
    }
}