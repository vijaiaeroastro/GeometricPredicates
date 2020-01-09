#include "point.hpp"

namespace GeometricPredicates
{
    // All the point 3 stuff
    Point_3::Point_3(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Point_3::Point_3(vbn::BigNumber _x, vbn::BigNumber _y, vbn::BigNumber _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Point_3::Point_3(Point_3 &_input_point)
    {
        *this = _input_point;
    }

    std::ostream& operator<<(std::ostream& stream,Point_3& input_point)
    {
        stream << "Point_3 -> ( X : " << input_point.getX().getDouble() << " Y : " << input_point.getY().getDouble() << " Z : " << input_point.getZ().getDouble() << " ) ";
        return stream;
    }

}