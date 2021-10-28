namespace twoDimension{
    struct Point{
        double x;
        double y;
        Point(double x = 0, double y = 0){
            this->x = x;
            this->y = y;
        }

        friend twoDimension::Point ConvertThreeDimensionalToTwoDimensional(threeDimension::Point &a);

    };

    twoDimension::Point ConvertThreeDimensionalToTwoDimensional(threeDimension::Point &a){
       twoDimension::Point p(a.x,a.y);
       return p; 
    }  

}
