#include <iostream>
#include <cmath>

#include <vector.h>

int main(){
    Vector a(1,2,3);
    Vector b(2,3,4);
    std::cout << a.getx() << std::endl;
    std::cout << a.gety() << std::endl;
    std::cout << a.dot(b) << std::endl;
}
