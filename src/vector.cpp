#include <vector.h>
#include <points.h>
#include <cmath>

double Vector::findMagnitude(){
    return sqrt((this->getx())*(this->getx()) + this->gety()*this->gety() + this->getz()*this->getz());
}

Vector Normalize(Vector a){
    Vector vec;
    vec.setX(a.getx()/a.findMagnitude());
    vec.setY(a.gety()/a.findMagnitude());
    vec.setZ(a.getz()/a.findMagnitude());
    return vec;
}

double Vector::getx(){
    return this->x;
}

double Vector::gety(){
    return this->y;
}

double Vector::getz(){
    return this->z;
}

void Vector::setX(double x){
    this->x = x;
}

void Vector::setY(double y){
    this->y = y;
}

void Vector::setZ(double z){
    this->z = z;
}

Vector::Vector(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector operator- (threeDimension::Point const&a, threeDimension::Point const&b){
    Vector vec;
    vec.setX(a.x - b.x);
    vec.setY(a.y - b.y);
    vec.setZ(a.z - b.z);

    return vec;
}


Vector operator- (twoDimension::Point const &a, twoDimension::Point const&b){
    Vector vec;
    vec.setX(a.x + b.x);
    vec.setY(a.y + b.y);
    vec.setZ(0);
    return vec;
}

Vector Vector::crossProduct(Vector a, Vector b){
    Vector vec;
    vec.setX(a.y*b.z - a.z*b.y);
    vec.setY(a.z*b.x - a.x*b.z);
    vec.setZ(a.x*b.y - a.y*b.x);

    return vec;
}

Vector Vector::crossProduct(Vector a){
    Vector vec;
    vec.setX(this->y*a.z - this->z*a.y);
    vec.setY(this->z*a.x - this->x*a.z);
    vec.setY(this->x*a.y - this->y*a.x);
    return vec;
}


double Vector::dot(Vector a, Vector b){
    return a.getx()*b.getx() + a.gety()+b.gety();
}

double Vector::dot(Vector a){
    return this->getx() * a.getx() + this->gety() * a.gety() + this->getz()*a.getz();
}

double Vector::dot(threeDimension::Point a){
    threeDimension::Point b;
    Vector vec = a - b;
    return this->dot(vec);
}

double Vector::dot(twoDimension::Point a){
    twoDimension::Point b;
    Vector vec = a - b; 
    return this->dot(vec); 
}

void barycentric(twoDimension::Point a, twoDimension::Point b, twoDimension::Point c,twoDimension::Point p, float &u, float &v, float &w){
    Vector v0 = b - a, v1 =  c - a, v2 = p - a;
    float d00 = v0.dot(v1);
    float d01 = v0.dot(v2);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    float denom = d00 * d11 - d01*d01;

    v = (d11 * d20 - d01 * d21)/denom;
    w = (d00*d21 - d01*d20) / denom;
    u = 1.0f - v - w;
}

Vector::Vector(Vector &vec){
    setX(vec.getx());
    setY(vec.gety());
    setZ(vec.getz());
}


struct Plane{
    Vector n;
    float d;
};

Plane ComputePlane(threeDimension::Point a, threeDimension::Point b, threeDimension::Point c){
    Plane p;
    p.n = Normalize((b-a).crossProduct(c-a));
    p.d = Normalize((b-a).crossProduct(c-a)).dot(a);
    return p;
}
