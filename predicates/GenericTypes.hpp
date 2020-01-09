#ifndef BIG_NUMBER
#define BIG_NUMBER

#include <iostream>
#include <ArbitraryPrecision/ArbitraryPrecision.hpp>

namespace vbn {
    class BigNumber: public std::error_code {
        public:
            BigNumber(){};
            BigNumber(double input_number);
            BigNumber(vbn::BigNumber& input_number);
            BigNumber& operator = (double input_number);
            ~BigNumber(){};

        public:
            friend BigNumber operator+(BigNumber& number_1, BigNumber& number_2);
            friend BigNumber operator-(BigNumber& number_1, BigNumber& number_2);
            friend BigNumber operator*(BigNumber& number_1, BigNumber& number_2);
            friend BigNumber operator/(BigNumber& number_1, BigNumber& number_2);
            friend std::ostream& operator<<(std::ostream& stream, BigNumber& number);

        public:
            template< typename T >
            BigNumber operator+(T& other_number)
            {
                RationalNumber new_number;
                vbn::BigNumber overload_scalar(other_number);
                new_number = getSource() + overload_scalar.getSource();
                created_number = new_number;
                return *this;
            }

            template< typename T >
            BigNumber operator-(T& other_number)
            {
                RationalNumber new_number;
                vbn::BigNumber overload_scalar(other_number);
                new_number = getSource() - overload_scalar.getSource();
                created_number = new_number;
                return *this;
            }

            template< typename T >
            BigNumber operator*(T& other_number)
            {
                RationalNumber new_number;
                vbn::BigNumber overload_scalar(other_number);
                new_number = getSource() * overload_scalar.getSource();
                created_number = new_number;
                return *this;
            }

            template< typename T >
            BigNumber operator/(T& other_number)
            {
                RationalNumber new_number;
                vbn::BigNumber overload_scalar(other_number);
                new_number = getSource() / overload_scalar.getSource();
                created_number = new_number;
                return *this;
            }

        public:
            double getDouble();
            RationalNumber getSource();

        private:
            double original_number;
            RationalNumber created_number;
    };
}

#endif