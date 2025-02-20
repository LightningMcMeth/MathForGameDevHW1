#include <iostream>
#include <bit>
#include <bitset>
#include <cinttypes>
#include <gtest/gtest.h>

//1)
//a) Create function to convert floating-point value to its bitwise representation.
uint32_t FloatToBytes(float const& value) {
    return *(reinterpret_cast<uint32_t const*>(&value));
}

uint64_t DoubleToBytes(double const& value) {
    return *(reinterpret_cast<uint64_t const*>(&value));
}

//b) Create function to convert bitwise representation of floating - point value to an actual floating - point value.
float BytesToFloat(uint32_t const& value) {
    return *(reinterpret_cast<float const*>(&value));
}

double BytesToDouble(uint64_t const& value) {
    return *(reinterpret_cast<double const*>(&value));
}


//2)
//f) Check if floating-point value is positive zero

bool isFloatZero(float const value) {
    uint32_t bitValue = FloatToBytes(value);

    return (bitValue & 0b11111111111111111111111111111111) == 0b00000000000000000000000000000000;
}

bool isDoubleZero(double const value) {
    uint64_t bitValue = DoubleToBytes(value);

    return (bitValue & 0b1111111111111111111111111111111111111111111111111111111111111111) ==
        0b0000000000000000000000000000000000000000000000000000000000000000;
}

//j) Check if floating-point value is subnormal value

bool isFloatSubnormal(float const value) {
    uint32_t bitValue = FloatToBytes(value);
    uint8_t exponent = bitValue >> 23;
    uint32_t mantissa = bitValue & 0b11111111111111111111111;

    return (exponent == 0b00000000) && (mantissa != 0b0000000000000000000000000000000);
}

bool isDoubleSubnormal(double const value) {
    uint32_t bitValue = DoubleToBytes(value);
    uint16_t exponent = bitValue >> 52;
    uint32_t mantissa = bitValue & 0b1111111111111111111111111111111111111111111111111111;

    return (exponent == 0b00000000) && (mantissa != 0b0000000000000000000000000000000000000000000000000000);
}
//c) Check if floating-point value is positive infinity value

bool isFloatPosInf(float value) {
    uint32_t bitValue = FloatToBytes(value);
    uint16_t exponent = bitValue >> 23;

    return exponent == 0b11111111;
}

bool isDoublePosInf(double value) {
    uint64_t bitValue = DoubleToBytes(value);
    uint16_t exponent = bitValue >> 52;

    return exponent == 0b11111111111;
}

//g) Check if floating-point value is negative zero value

bool isFloatNegZero(float const value) {
    uint32_t bitValue = FloatToBytes(value);

    return (bitValue & 0b11111111111111111111111111111111) != 0b00000000000000000000000000000000;
}

bool isDoubleNegZero(double const value) {
    uint64_t bitValue = DoubleToBytes(value);

    return (bitValue & 0b1111111111111111111111111111111111111111111111111111111111111111) !=
        0b0000000000000000000000000000000000000000000000000000000000000000;
}

//h) Check if floating-point value is not a number value

bool isFloatNaN(float const value) {
    uint32_t bitValue = FloatToBytes(value);
    uint8_t exponent = bitValue >> 23;
    uint32_t mantissa = bitValue & 0b11111111111111111111111;

    return (exponent == 0b11111111) && (mantissa != 0b0000000000000000000000000000000);
}

bool isDoubleNaN(double const value) {
    uint64_t bitValue = DoubleToBytes(value);
    uint8_t exponent = bitValue >> 52;
    uint32_t mantissa = bitValue & 0b1111111111111111111111111111111111111111111111111111;

    return (exponent == 0b11111111) && (mantissa != 0b0000000000000000000000000000000000000000000000000000);
}

//i) Check if floating-point value is normal value

bool isFloatNormal(float const value) {
    uint32_t bitValue = FloatToBytes(value);
    uint8_t exponent = bitValue >> 23;

    return (exponent >= 0b00000001) && (exponent <= 0b11111110);
}

bool isDoubleNormal(double const value) {
    uint64_t bitValue = DoubleToBytes(value);
    uint16_t exponent = bitValue >> 52;

    return (exponent >= 0b00000001) && (exponent <= 0b11111110);
}

//k) Check if floating-point value is signed

bool isFloatSigned(float const value) {
    uint32_t bitValue = FloatToBytes(value);

    return (bitValue >> 31) == 0b1;
}

bool isDoubleSigned(double const value) {
    uint64_t bitValue = DoubleToBytes(value);

    return (bitValue >> 63) == 0b1;
}

//d) Check if floating-point value is negative infinity value

bool isFloatNegInf(float value) {
    uint32_t bitValue = FloatToBytes(value);
    uint16_t exponent = (bitValue >> 22) & 0b111111111; //we shift less to accommodate for the sign

    return exponent == 0b111111111;
}

bool isDoubleNegInf(double const value) {
    uint64_t bitValue = DoubleToBytes(value);
    uint16_t exponent = (bitValue >> 51) & 0b111111111111; //we shift less to accommodate for the sign

    return exponent == 0b111111111111;
}

//a) Check if floating-point value is finite value

bool isFiniteFloat(float const& value) {
    return  (isFloatNormal(value) || isFloatSubnormal(value) || isFloatZero(value));
}

bool isFiniteDouble(double const& value) {
    return (isDoubleNormal(value) || isDoubleSubnormal(value) || isDoubleZero(value));
}

//b) Check if floating-point value is any infinity value

bool isFloatInf(float value) {
    if (!isFloatPosInf(value)) {
        return isFloatNegInf(value);
    }
    return 0;
}

bool isDoubleInf(double value) {
    if (!isDoublePosInf(value)) {
        return isDoubleNegInf(value);
    }
    return 0;
}

//e) Check if floating-point value is any zero value

bool isFloatAnyZero(float const value) {
    if (!isFloatZero(value)) {
        return isFloatNegZero(value);
    }
    return 0;
}


bool isDoubleAnyZero(double const value) {
    if (!isDoubleZero(value)) {
        return isDoubleNegZero(value);
    }
    return 0;
}

//l) Classify floating-point value

enum FPType {
    ZERO,
    SUBNORMAL,
    NORMAL,
    INFINITE,
    NaN,
    I_DUNNO_LOL,
};

FPType fpClassify(float const value) {

    if (isFloatAnyZero(value)) {
        return ZERO;
    }
    else if (isFloatSubnormal(value)) {
        return SUBNORMAL;
    }
    else if (isFloatNormal(value)) {
        return NORMAL;
    }
    else if (isFloatInf(value)) {
        return INFINITE;
    }
    else if (isFloatNaN(value)) {
        return NaN;
    }
    
    return I_DUNNO_LOL;
}

FPType fpClassify(double const value) {

    if (isDoubleAnyZero(value)) {
        return ZERO;
    }
    else if (isDoubleSubnormal(value)) {
        return SUBNORMAL;
    }
    else if (isDoubleNormal(value)) {
        return NORMAL;
    }
    else if (isDoubleInf(value)) {
        return INFINITE;
    }
    else if (isDoubleNaN(value)) {
        return NaN;
    }

    return I_DUNNO_LOL;
}

//3)
//a) To get an absolute value of floating-point value.

float absFloat(float const value) {
    uint32_t bitValue = FloatToBytes(value);

    return bitValue & 0b01111111111111111111111111111111;
}

double absDouble(double const value) {
    uint32_t bitValue = FloatToBytes(value);

    return bitValue & 0b0111111111111111111111111111111111111111111111111111111111111111;
}

//b) To get min of two values of floating-point value.

bool comp(float const a, float const b) {
    return b < a;
}

bool comp(double const a, double const b) {
    return b < a;
}

float min(float const a, float const b) {
    return comp(a, b) ? b : a;
}

double min(double const a, double const b) {
    return comp(a, b) ? b : a;
}

//c) To get max of two values of floating-point value.

float max(float const a, float const b) {
    return !comp(a, b) ? b : a;
}

double max(double const a, double const b) {
    return !comp(a, b) ? b : a;
}

//d) To clamp between two floating-point values.

float clamp(float const low, float const high, float const value) {
    return comp(low, value) ? low : comp(value, high) ? high : value;
}

double clamp(double const low, double const high, double const value) {
    return comp(low, value) ? low : comp(value, high) ? high : value;
}

//4)
//a) Compare two floating-point values for equality with specified precision.

bool areFloatsEqualWithPrecision(float const a, float const b, float const precision) {
    return abs(a - b) < precision;
}

bool areDoublesEqualWithPrecision(double const a, double const b, double const precision) {
    return abs(a - b) < precision;
}

//b) Compare two arbitrary floating-point values for equality.

bool areFloatsEqual(float const a, float const b) {
    return a == b;
}

bool areDoublesEqual(double const a, double const b) {
    return a == b;
}

//c) Compare two floating-point values for through less operator with specified precision.

bool isFloatLessWithPrecision(float const a, float const b, float const precision) {
    return (a + precision) < b;
}

bool isDoubleLessWithPrecision(double const a, double const b, double const precision) {
    return (a + precision) < b;
}

//d) Compare two arbitrary floating-point values through less operator.

bool isFloatLess(float const a, float const b) {
    return a < b;
}

bool isDoubleLess(double const a, double const b) {
    return a < b;
}

//e) Compare two floating-point values for greater operator with specified precision.

bool isFloatGreaterWithPrecision(float const a, float const b, float const precision) {
    return a > (b + precision);
}

bool isDoubleGreaterWithPrecision(double const a, double const b, double const precision) {
    return a > (b + precision);
}

//f) Compare two arbitrary floating-point values through greater operator.

bool isFloatGreater(float const a, float const b) {
    return a > b;
}

bool isDoubleGreater(double const a, double const b) {
    return a > b;
}

TEST(FloatConversionTests, CheckIfValuesAreEven) {
    EXPECT_EQ(FloatToBytes(1.0f), 0b00111111100000000000000000000000);
    EXPECT_EQ(FloatToBytes(-1.0f), 0b10111111100000000000000000000000);
}

int main()
{


    return 0;
}
