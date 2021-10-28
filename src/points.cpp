#include <points.h>

namespace threeDimension{
    Point::Point(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
}

namespace twoDimension{
    
    Point::Point(double x, double y){
        this->x = x;
        this->y = y;
    }

    Point ConvertThreeDimensionalToTwoDimensional(threeDimension::Point &a){
       Point p(a.x,a.y);
       return p; 
    }

}
