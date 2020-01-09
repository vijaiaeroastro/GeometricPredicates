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
            BigNumber operator+(BigNumber& other_number);
            BigNumber operator-(BigNumber& other_number);
            BigNumber operator*(BigNumber& other_number);
            BigNumber operator/(BigNumber& other_number);

        public:
            double getDouble();
            RationalNumber getSource();

        private:
            double original_number;
            RationalNumber created_number;
    };
}

#endif