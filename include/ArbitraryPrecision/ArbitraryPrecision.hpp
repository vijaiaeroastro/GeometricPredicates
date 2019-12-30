// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

#pragma once

#include <ArbitraryPrecision/UIntegerALU32.hpp>
#include <ArbitraryPrecision/UIntegerAP32.hpp>
#include <ArbitraryPrecision/UIntegerFP32.hpp>
#include <ArbitraryPrecision/BSNumber.hpp>
#include <ArbitraryPrecision/BSRational.hpp>
#include <ArbitraryPrecision/BSPrecision.hpp>

using RationalNumber = gte::BSRational< gte::UIntegerFP32< 50 > >;
using BigInteger = gte::BSNumber< gte::UIntegerFP32< 50 > >;