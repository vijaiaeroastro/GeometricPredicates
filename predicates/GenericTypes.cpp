#include "GenericTypes.hpp"
#include <ArbitraryPrecision/ArbitraryPrecision.hpp>

namespace vbn
{
    BigNumber& BigNumber::operator = (double input_number)
    {
        original_number = input_number;
        created_number = input_number;
        return *this;
    }

    BigNumber::BigNumber(double input_number)
    {
        original_number = input_number;
        created_number = input_number;
    }

    BigNumber::BigNumber(vbn::BigNumber& input_number)
    {
        original_number = input_number.getDouble();
        created_number = input_number.getSource();
    }

    double BigNumber::getDouble()
    {
        return original_number;
    }

    RationalNumber BigNumber::getSource()
    {
        return created_number;
    }

    // All the overloaded operators
    BigNumber BigNumber::operator+(BigNumber& other_number)
    {
        RationalNumber created_number = original_number;
        created_number = created_number + other_number.getSource();
    }

    BigNumber BigNumber::operator-(BigNumber& other_number)
    {
        created_number = created_number - other_number.getSource();
    }

    BigNumber BigNumber::operator*(BigNumber& other_number)
    {
        created_number = created_number * other_number.getSource();
    }

    BigNumber BigNumber::operator/(BigNumber& other_number)
    {
        created_number = created_number / other_number.getSource();
    }

    // All the friendlies of our class
    BigNumber operator+(BigNumber& number_1, BigNumber& number_2)
    {
        BigNumber new_number(number_1.getSource() + number_2.getSource());
        return new_number;
    }

    BigNumber operator-(BigNumber& number_1, BigNumber& number_2)
    {
        BigNumber new_number(number_1.getSource() - number_2.getSource());
        return new_number;
    }
    BigNumber operator*(BigNumber& number_1, BigNumber& number_2)
    {
        BigNumber new_number(number_1.getSource() * number_2.getSource());
        return new_number;
    }
    BigNumber operator/(BigNumber& number_1, BigNumber& number_2)
    {
        BigNumber new_number(number_1.getSource() / number_2.getSource());
        return new_number;
    }

    std::ostream& operator<<(std::ostream& stream, BigNumber& number)
    {
        double converted_value = number.getDouble();
        stream << converted_value << "[BN]";
        return stream;
    }
}