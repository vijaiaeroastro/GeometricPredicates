#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include "GenericTypes.hpp"

namespace GeometricPredicates
{
    // Forward declaration of 3d point type
    class Point_3;

    // Point 3 type declaration
    class Point_3
    {
        public:
            Point_3(double _x, double _y, double _z);
            Point_3(vbn::BigNumber _x, vbn::BigNumber _y, vbn::BigNumber _z);
            Point_3(Point_3 &_input_point);
            ~Point_3(){};

        public:
            template< typename T >
            Point_3 operator+(T _scalar)
            {
                vbn::BigNumber new_scalar(_scalar);
                this->x = this->x + new_scalar;
                this->y = this->y + new_scalar;
                this->z = this->z + new_scalar;
                return *this;
            }

            template< typename T >
            Point_3 operator-(T _scalar)
            {
                vbn::BigNumber new_scalar(_scalar);
                this->x = this->x - new_scalar;
                this->y = this->y - new_scalar;
                this->z = this->z - new_scalar;
                return *this;
            }

            template< typename T >
            Point_3 operator*(T _scalar)
            {
                vbn::BigNumber new_scalar(_scalar);
                this->x = this->x * new_scalar;
                this->y = this->y * new_scalar;
                this->z = this->z * new_scalar;
                return *this;
            }

            template< typename T >
            Point_3 operator/(T _scalar)
            {
                vbn::BigNumber new_scalar(_scalar);
                this->x = this->x / new_scalar;
                this->y = this->y / new_scalar;
                this->z = this->z / new_scalar;
                return *this;
            }

        public:
        vbn::BigNumber Dot(Point_3 _another_point)
        {
            vbn::BigNumber x_portion, y_portion, z_portion, another_x, another_y, another_z, dot_product;
            another_x = _another_point.getX();
            another_y = _another_point.getY();
            another_z = _another_point.getZ();
            x_portion = this->getX() * another_x;
            y_portion = this->getY() * another_y;
            z_portion = this->getZ() * another_z;
            dot_product = x_portion + y_portion + z_portion;
            return dot_product;
        }

        Point_3 Cross(Point_3 _another_point)
        {
            vbn::BigNumber another_x, another_y, another_z;
            another_x = _another_point.getX(); another_y = _another_point.getY(); another_z = _another_point.getZ();
            vbn::BigNumber cross_x1, cross_x2, cross_y1, cross_y2, cross_z1, cross_z2;
            cross_x1 = (this->y * another_z); cross_x2 = (this->z * another_y);
            cross_y1 = (this->z * another_x); cross_y2 = (this->x * another_z);
            cross_z1 = (this->x * another_y); cross_z2 = (this->y * another_x);
            vbn::BigNumber cross_x, cross_y, cross_z;
            cross_x = cross_x1 - cross_x2;
            cross_y = cross_y1 - cross_y2;
            cross_z = cross_z1 - cross_z2;
            Point_3 cross_product(cross_x, cross_y, cross_z);
            return cross_product;
        }

        vbn::BigNumber Norm()
        {
            vbn::BigNumber x_portion, y_portion, z_portion;
            x_portion = this->x * this->x;
            y_portion = this->y * this->y;
            z_portion = this->z * this->z;
            vbn::BigNumber truncation;
            truncation = (x_portion + y_portion + z_portion);
            double truncated_sqrt = std::sqrt(truncation.getDouble());
            vbn::BigNumber resulting_norm(truncated_sqrt);
            return resulting_norm;
        }

        vbn::BigNumber Length()
        {
            vbn::BigNumber length_result;
            length_result = Norm();
            return length_result;
        }

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