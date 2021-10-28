#ifndef POINTS_H
#define POINTS_H

namespace threeDimension{
    
    struct Point{
        double x;
        double y;
        double z;
        Point(double x = 0, double y = 0, double z = 0);
    };

}

namespace twoDimension{
    struct Point{
        double x;
        double y;
        Point(double x = 0, double y = 0);
        friend Point ConvertThreeDimensionalToTwoDimensional(threeDimension::Point &a);
    };

}

#endif