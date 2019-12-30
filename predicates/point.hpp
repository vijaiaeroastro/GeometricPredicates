#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include "GenericTypes.hpp"

namespace GeometricPredicates
{
    // Forward declaration of 2d and 3d point types
    class Point_2;
    class Point_3;

    // Point 2 type declaration
    class Point_2
    {
        public:
            Point_2(double _x, double _y);
            Point_2(vbn::BigNumber _x, vbn::BigNumber _y);
            Point_2(Point_2 &_input_point);
            Point_2(Point_3 &_input_point);
            ~Point_2(){};

        public:
            template < typename T>
                void setX(T _x){ x = _x; };
            template < typename T>
                void setY(T _y){ y = _y; };
            vbn::BigNumber getX()
            {
                return x;
            };
            vbn::BigNumber getY(){ return y; };

        public:
            friend std::ostream& operator<<(std::ostream& stream, Point_2& input_point);

        private:
            vbn::BigNumber x, y;
    };

    // Point 3 type declaration
    class Point_3
    {
        public:
            Point_3(double _x, double _y, double _z);
            Point_3(vbn::BigNumber _x, vbn::BigNumber _y, vbn::BigNumber _z);
            Point_3(Point_3 &_input_point);
            Point_3(Point_2 &_input_point);
            ~Point_3(){};

        public:
            template < typename T>
                void setX(T _x){ x = _x; };
            template < typename T>
                void setY(T _y){ y = _y; };
            template < typename T>
                void setZ(T _z){ z = _z; };
            vbn::BigNumber getX(){ return x; };
            vbn::BigNumber getY(){ return y; };
            vbn::BigNumber getZ(){ return z; };

        public:
            friend std::ostream& operator<<(std::ostream& stream, Point_3& input_point);

        private:
            vbn::BigNumber x, y, z;
    };

}

#endif