#include <iostream>
#include <ArbitraryPrecision/ArbitraryPrecision.hpp>
#include "predicates/point.hpp"

void direct_test();
void generic_type_implementation_test();
void point_tests();

int main()
{
//    direct_test();
//    generic_type_implementation_test();
    point_tests();
    return 0;
}

void point_tests()
{
    using namespace GeometricPredicates;
    Point_2 p1(0.1,2.1);
    Point_3 p2(0.0, 1.0, 2.0);
    std::cout << p2 << std::endl;
    std::cout << p1 << std::endl;
}

void generic_type_implementation_test()
{
    vbn::BigNumber n1(3.1415);
    std::cout << n1 << std::endl;
}

void direct_test()
{
    gte::BSRational< gte::UIntegerFP32< 100 > > number_1;
    gte::BSRational< gte::UIntegerFP32< 100 > > number_2;
    number_1 = 5.0;
    number_2 = 2.0;
    gte::BSRational< gte::UIntegerFP32< 100 > > result;
    result = number_1 / number_2;
    double double_res = result;
}