#ifndef VECTOR_H
#define VECTOR_H

#include "points.h"

class Vector{
    private:

        double x;
        double y;
        double z;

    public:
        Vector(double x, double y, double z);
        Vector(Vector &vec);
        Vector();

        friend Vector operator - (Vector&a, Vector&b);
        friend Vector operator + (Vector&,Vector&);

        void printVector();
        double getx();
        double gety(); 
        double getz();
        void setX(double x);
        void setY(double y);
        void setZ(double z);

        friend Vector operator - (threeDimension::Point const &a, threeDimension::Point &b);
        
        double findMagnitude();

        double dot(Vector , Vector );
        double dot(Vector );

        double dot(twoDimension::Point);
        double dot(threeDimension::Point);
        
        Vector crossProduct(Vector , Vector);
        Vector crossProduct(Vector);
    
        friend Vector operator - (twoDimension::Point const &a, twoDimension::Point &b);

        Vector operator-=(Vector refVector);
        Vector operator+=(Vector refVector);

        friend Vector operator*(Vector ref,float f);
        friend Vector operator*(float f,Vector ref);


};

#endif