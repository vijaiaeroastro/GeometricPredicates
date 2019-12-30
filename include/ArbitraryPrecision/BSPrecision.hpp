// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>

// Support for determining the number of bits of precision required to compute
// an expression.  See the document
//   https://www.geometrictools.com/Documentation/ArbitraryPrecision.pdf
// for an example of how to use this class.

namespace gte
{
    class BSPrecision
    {
    public:
        // This constructor is used for 'float' or 'double'.  The
        // floating-point inputs for the expressions have no restrictions;
        // that is, the inputs can be any finite floating-point numbers,
        // normal or subnormal.
        BSPrecision(bool isFloat, bool forBSNumber)
            :
            mForBSNumber(forBSNumber)
        {
            // It is not clear what the rationale is for the C++ Standard
            // Library to set numeric_limits<float>::min_exponent to -125
            // instead of -126.  The same issue arises with
            // numeric_limits<double>::min_exponent set to -1021 instead of
            // -1022.  Similarly, it is not clear why
            // numeric_limits<float>::max_exponent is set to 128 when the
            // maximum finite 'float' has exponent 127.  The exponent 128 is
            // used in the 'float' infinity, but treating this as 2^{128} does
            // not seem to be consistent with the IEEE 754-2008 standard.
            // The same issue occurs with numeric_limits<double>::max_exponent
            // set to 1024 rather than 1023.

            if (isFloat)
            {
                // mNumBits = 24
                mNumBits = std::numeric_limits<float>::digits;
                // mMinBiasedExponent = -149
                mMinBiasedExponent = std::numeric_limits<float>::min_exponent - mNumBits;
                // mMaxExponent = 127
                mMaxExponent = std::numeric_limits<float>::max_exponent - 1;
            }
            else
            {
                // mNumBits = 53
                mNumBits = std::numeric_limits<double>::digits;
                // mMinBiasedExponent = -1074
                mMinBiasedExponent = std::numeric_limits<double>::min_exponent - mNumBits;
                // mMaxExponent = 1023
                mMaxExponent = std::numeric_limits<double>::max_exponent - 1;
            }
        }

        // If you know that your inputs are limited in magnitude, use this
        // constructor.  For example, if you know that your inputs x satisfy
        // |x| <= 8, you can specify maxExponent of 3.  The minimum power will
        // still be that for the smallest positive subnormal.
        BSPrecision(bool isFloat, int32_t maxExponent, bool forBSNumber)
            :
            mForBSNumber(forBSNumber)
        {
            if (isFloat)
            {
                // mNumBits = 24
                mNumBits = std::numeric_limits<float>::digits;
                // mMinBiasedExponent = -149
                mMinBiasedExponent = std::numeric_limits<float>::min_exponent - mNumBits;
                mMaxExponent = maxExponent;
            }
            else
            {
                // mNumBits = 53
                mNumBits = std::numeric_limits<double>::digits;
                // mMinBiasedExponent = -1074
                mMinBiasedExponent = std::numeric_limits<double>::min_exponent - mNumBits;
                mMaxExponent = maxExponent;
            }
        }

        // You must use this constructor carefully based on knowledge of your
        // expressions.  For example, if you know that your inputs are 'float'
        // and in the interval [1,2), you would choose 24 for the number of
        // bits of precision, a minimum biased exponent of -23 because the
        // largest 'float' smaller than 2 is 1.1^{23}*2^0 = 1^{24}*2^{-23},
        // and a maximum exponent of 0.  These numbers work to determine bits
        // of precision to compute x*y+z*w.  However, if you then compute an
        // expression such as x-y for x and y in [1,2) and multiply by powers
        // of 1/2, the bit counting will not be correct because the results
        // can be subnormals where the minimum biased exponent is -149,
        // not -23.
        BSPrecision(int32_t numBits, int32_t minBiasedExponent, int32_t maxExponent, bool forBSNumber)
            :
            mNumBits(numBits),
            mMinBiasedExponent(minBiasedExponent),
            mMaxExponent(maxExponent),
            mForBSNumber(forBSNumber)
        {
        }

        // Member access.
        inline int32_t GetNumWords() const
        {
            return mNumBits / 32 + ((mNumBits % 32) > 0 ? 1 : 0);
        }

        inline int32_t GetNumBits() const
        {
            return mNumBits;
        }

        inline int32_t GetMinBiasedExponent() const
        {
            return mMinBiasedExponent;
        }

        inline int32_t GetMinExponent() const
        {
            return mMinBiasedExponent + mNumBits - 1;
        }

        inline int32_t GetMaxExponent() const
        {
            return mMaxExponent;
        }

        // Support for determining the number of bits of precision required to
        // compute an expression using BSNumber or BSRational.
        BSPrecision operator*(BSPrecision const& precision)
        {
            // BSRational operator* involves a product of numerators and a
            // product of denominators.  In worst case, the precision
            // requirements are the same as a BSNumber operator*, so testing
            // of mForBSNumber is not needed.
            int32_t numBits = mNumBits + precision.mNumBits;
            int32_t maxExponent = mMaxExponent + precision.mMaxExponent + 1;
            int32_t minBiasedExponent = mMinBiasedExponent + precision.mMinBiasedExponent;
            return BSPrecision(numBits, minBiasedExponent, maxExponent, mForBSNumber);
        }

        BSPrecision operator+(BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                int32_t minBiasedExponent = std::min(mMinBiasedExponent, precision.mMinBiasedExponent);
                int32_t maxExponent = std::max(mMaxExponent, precision.mMaxExponent) + 1;
                int32_t numBits = maxExponent - minBiasedExponent;
                return BSPrecision(numBits, minBiasedExponent, maxExponent, mForBSNumber);
            }
            else
            {
                // n0/d0 + n1/d1 = (n0*d1 + n1*d0) / (d0*d1)
                BSPrecision product = operator*(precision);
                product.mForBSNumber = true;
                BSPrecision sum = product + product;
                sum.mForBSNumber = false;
                BSPrecision division = sum / product;
                division.mForBSNumber = false;
                return division;
            }
        }

        BSPrecision operator-(BSPrecision const& precision)
        {
            return operator+(precision);
        }

        // Support for determining the number of bits of precision required to
        // compute a BSRational expression (operations not relevant for
        // BSNumber).
        BSPrecision operator/(BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                return precision;
            }
            else
            {
                // Division leads to multiplication of numerators and
                // denominators.
                return operator*(precision);
            }
        }

        BSPrecision operator==(BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                return precision;
            }
            else
            {
                // Comparison leads to multiplication of numerators and
                // denominators.
                return operator*(precision);
            }
        }

        BSPrecision operator!=(BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                return precision;
            }
            else
            {
                // Comparison leads to multiplication of numerators and
                // denominators.
                return operator*(precision);
            }
        }

        BSPrecision operator< (BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                return precision;
            }
            else
            {
                // Comparison leads to multiplication of numerators and
                // denominators.
                return operator*(precision);
            }
        }

        BSPrecision operator<=(BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                return precision;
            }
            else
            {
                // Comparison leads to multiplication of numerators and
                // denominators.
                return operator*(precision);
            }
        }

        BSPrecision operator> (BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                return precision;
            }
            else
            {
                // Comparison leads to multiplication of numerators and
                // denominators.
                return operator*(precision);
            }
        }

        BSPrecision operator>=(BSPrecision const& precision)
        {
            if (mForBSNumber)
            {
                return precision;
            }
            else
            {
                // Comparison leads to multiplication of numerators and
                // denominators.
                return operator*(precision);
            }
        }

    private:
        int32_t mNumBits, mMinBiasedExponent, mMaxExponent;
        bool mForBSNumber;
    };
}
