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
    uint64_t bitValue = DoubleToBytes(value);
    uint16_t exponent = bitValue >> 52;
    uint32_t mantissa = bitValue & 0b1111111111111111111111111111111111111111111111111111;

    return (exponent == 0b00000000) && (mantissa != 0b0000000000000000000000000000000000000000000000000000);
}
//c) Check if floating-point value is positive infinity value

bool isFloatPosInf(float value) {
    uint32_t bitValue = FloatToBytes(value);
    return bitValue == (0b011111111000000000000000000000000);
}

bool isDoublePosInf(double value) {
    uint64_t bitValue = DoubleToBytes(value);
    return bitValue == (0b0111111111110000000000000000000000000000000000000000000000000000);
}

//g) Check if floating-point value is negative zero value

bool isFloatNegZero(float const value) {
    uint32_t bitValue = FloatToBytes(value);

    return bitValue == (0b10000000000000000000000000000000);
}

bool isDoubleNegZero(double const value) {
    uint64_t bitValue = DoubleToBytes(value);

    return bitValue == (0b1000000000000000000000000000000000000000000000000000000000000000);
}

//h) Check if floating-point value is not a number value

bool isFloatNaN(float const value) {
    uint32_t bitValue = FloatToBytes(value);
    uint8_t exponent = bitValue >> 23;
    uint32_t mantissa = bitValue & 0b11111111111111111111111;

    return (exponent == 0b11111111) && (mantissa != 0);
}

bool isDoubleNaN(double const value) {
    uint64_t bitValue = DoubleToBytes(value);
    uint16_t exponent = bitValue >> 52;
    uint64_t mantissa = bitValue & 0b1111111111111111111111111111111111111111111111111111;

    return (exponent == 0b11111111) && (mantissa != 0);
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

    return (exponent >= 0b00000000001) && (exponent <= 0b11111111110);
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
    return bitValue == (0b11111111100000000000000000000000);
}

bool isDoubleNegInf(double const value) {
    uint64_t bitValue = DoubleToBytes(value);
    return bitValue == (0b1111111111110000000000000000000000000000000000000000000000000000);
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

    return BytesToFloat(bitValue & 0b01111111111111111111111111111111);
}

double absDouble(double const value) {
    uint32_t bitValue = FloatToBytes(value);

    return BytesToDouble(bitValue & 0b0111111111111111111111111111111111111111111111111111111111111111);
}

//b) To get min of two values of floating-point value.

bool compFloat(float const a, float const b) {
    return b < a;
}

bool compDouble(double const a, double const b) {
    return b < a;
}

float minFloat(float const a, float const b) {
    return compFloat(a, b) ? b : a;
}

double minDouble(double const a, double const b) {
    return compDouble(a, b) ? b : a;
}

//c) To get max of two values of floating-point value.

float maxFloat(float const a, float const b) {
    return !compFloat(a, b) ? b : a;
}

double maxDouble(double const a, double const b) {
    return !compDouble(a, b) ? b : a;
}

//d) To clamp between two floating-point values.

float clampFloat(float const low, float const high, float const value) {
    return compFloat(low, value) ? low : compFloat(value, high) ? high : value;
}

double clampDouble(double const low, double const high, double const value) {
    return compDouble(low, value) ? low : compDouble(value, high) ? high : value;
}

//4)
//a) Compare two floating-point values for equality with specified precision.

bool areFloatsEqualWithPrecision(float const a, float const b, float const precision) {
    return absFloat(a - b) < precision;
}

bool areDoublesEqualWithPrecision(double const a, double const b, double const precision) {
    return absDouble(a - b) < precision;
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
    EXPECT_EQ(FloatToBytes(3.3f), 0b01000000010100110011001100110011);
    EXPECT_EQ(FloatToBytes(NAN), 0b01111111110000000000000000000000);
    EXPECT_EQ(FloatToBytes(0.0f), 0b00000000000000000000000000000000);
    EXPECT_EQ(FloatToBytes(-0.0f), 0b10000000000000000000000000000000);

    EXPECT_EQ(BytesToFloat(0b00111111100000000000000000000000), 1.0f);
    EXPECT_EQ(BytesToFloat(0b10111111100000000000000000000000), -1.0f);
    EXPECT_EQ(BytesToFloat(0b01000000010100110011001100110011), 3.3f);
    EXPECT_EQ(BytesToFloat(0b01111111110000000000000000000000), NAN);
    EXPECT_EQ(BytesToFloat(0b00000000000000000000000000000000), 0.0f);
    EXPECT_EQ(BytesToFloat(0b10000000000000000000000000000000), -0.0f);
}

TEST(DoubleConversionTests, CheckIfValuesAreEven) {
    EXPECT_EQ(DoubleToBytes(1.0), 0b0011111111110000000000000000000000000000000000000000000000000000);
    EXPECT_EQ(DoubleToBytes(-1.0), 0b1011111111110000000000000000000000000000000000000000000000000000);
    EXPECT_EQ(DoubleToBytes(3.3), 0b0100000000001010011001100110011001100110011001100110011001100110);
    EXPECT_EQ(DoubleToBytes(NAN), 0b0111111111111000000000000000000000000000000000000000000000000000);
    EXPECT_EQ(DoubleToBytes(0.0), 0b0000000000000000000000000000000000000000000000000000000000000000);
    EXPECT_EQ(DoubleToBytes(-0.0), 0b1000000000000000000000000000000000000000000000000000000000000000);

    EXPECT_EQ(BytesToDouble(0b0011111111110000000000000000000000000000000000000000000000000000), 1.0);
    EXPECT_EQ(BytesToDouble(0b1011111111110000000000000000000000000000000000000000000000000000), -1.0);
    EXPECT_EQ(BytesToDouble(0b0100000000001010011001100110011001100110011001100110011001100110), 3.3);
    EXPECT_EQ(BytesToDouble(0b0111111111111000000000000000000000000000000000000000000000000000), NAN);
    EXPECT_EQ(BytesToDouble(0b0000000000000000000000000000000000000000000000000000000000000000), 0.0);
    EXPECT_EQ(BytesToDouble(0b1000000000000000000000000000000000000000000000000000000000000000), -0.0);
}

TEST(FloatIsZeroTests, sample_text_cuz_i_dunno) {
    EXPECT_FALSE(isFloatZero(1.0f));
    EXPECT_FALSE(isFloatZero(INFINITY));
    EXPECT_FALSE(isFloatZero(NAN));
    EXPECT_FALSE(isFloatZero(NAN));
    EXPECT_TRUE(isFloatZero(0.0f));
    EXPECT_FALSE(isFloatZero(-0.0f));
}

TEST(DoubleIsZeroTests, sample_text_cuz_i_dunno) {
    EXPECT_FALSE(isDoubleZero(-0.0));
    EXPECT_FALSE(isDoubleZero(INFINITY));
    EXPECT_FALSE(isDoubleZero(1.0));
    EXPECT_FALSE(isDoubleZero(NAN));
    EXPECT_TRUE(isDoubleZero(0.0));
}

TEST(DoubleIsPositiveInfinity, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isDoublePosInf(INFINITY));
    EXPECT_FALSE(isDoublePosInf(-INFINITY));
    EXPECT_FALSE(isDoublePosInf(1.0));
    EXPECT_FALSE(isDoublePosInf(NAN));
}

TEST(FloatIsPositiveInfinity, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFloatPosInf(INFINITY));
    EXPECT_FALSE(isFloatPosInf(-INFINITY));
    EXPECT_FALSE(isFloatPosInf(1.0f));
    EXPECT_FALSE(isFloatPosInf(NAN));
}

TEST(FloatIsNegativeZero, sample_text_cuz_i_dunno) {
    EXPECT_FALSE(isFloatNegZero(1.0f));
    EXPECT_FALSE(isFloatNegZero(INFINITY));
    EXPECT_FALSE(isFloatNegZero(0.0f));
    EXPECT_TRUE(isFloatNegZero(-0.0f));
    EXPECT_FALSE(isFloatNegZero(NAN));
}

TEST(DoubleIsNegativeZero, sample_text_cuz_i_dunno) {
    EXPECT_FALSE(isDoubleNegZero(0.0));
    EXPECT_TRUE(isDoubleNegZero(-0.0));
    EXPECT_FALSE(isDoubleNegZero(1.0));
    EXPECT_FALSE(isDoubleNegZero(INFINITY));
    EXPECT_FALSE(isDoubleNegZero(NAN));
}

TEST(FloatIsFinite, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFiniteFloat(1.0f));
    EXPECT_TRUE(isFiniteFloat(0.0f));
    EXPECT_FALSE(isFiniteFloat(INFINITY));
    EXPECT_FALSE(isFiniteFloat(NAN));
}

TEST(DoubleIsFinite, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFiniteDouble(1.0));
    EXPECT_TRUE(isFiniteDouble(0.0));
    EXPECT_FALSE(isFiniteDouble(INFINITY));
    EXPECT_FALSE(isFiniteDouble(NAN));
}

TEST(FloatIsInfinite, sample_text_cuz_i_dunno) {
    EXPECT_FALSE(isFloatInf(1.0f));
    EXPECT_FALSE(isFloatInf(0.0f));
    EXPECT_FALSE(isFloatInf(NAN));
    EXPECT_TRUE(isFloatInf(INFINITY));
    EXPECT_TRUE(isFloatInf(-INFINITY));
}

TEST(DoubleIsInfinite, sample_text_cuz_i_dunno) {
    EXPECT_FALSE(isDoubleInf(1.0));
    EXPECT_FALSE(isDoubleInf(0.0));
    EXPECT_FALSE(isDoubleInf(NAN));
    EXPECT_TRUE(isDoubleInf(INFINITY));
    EXPECT_TRUE(isDoubleInf(-INFINITY));
}

TEST(FloatIsFloatAnyZero, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFloatAnyZero(0.0f));
    EXPECT_FALSE(isFloatAnyZero(1.0f));
    EXPECT_TRUE(isFloatAnyZero(-0.0f));
    EXPECT_FALSE(isFloatAnyZero(NAN));
}

TEST(DoubleIsFloatAnyZero, sample_text_cuz_i_dunno) {
    EXPECT_FALSE(isDoubleAnyZero(1.0));
    EXPECT_FALSE(isDoubleAnyZero(NAN));
    EXPECT_TRUE(isDoubleAnyZero(0.0));
    EXPECT_TRUE(isDoubleAnyZero(-0.0));
}

TEST(FloatClassifyTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(fpClassify(0.0f), ZERO);
    EXPECT_EQ(fpClassify(-0.0f), ZERO);
    EXPECT_EQ(fpClassify(1.0f), NORMAL);
    EXPECT_EQ(fpClassify(INFINITY), INFINITE);
    EXPECT_EQ(fpClassify(NAN), NaN);
}

TEST(DoubleClassifyTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(fpClassify(0.0), ZERO);
    EXPECT_EQ(fpClassify(-0.0), ZERO);
    EXPECT_EQ(fpClassify(1.0), NORMAL);
    EXPECT_EQ(fpClassify(INFINITY), INFINITE);
    EXPECT_EQ(fpClassify(NAN), NaN);
}

TEST(FloatMinTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(minFloat(1.0f, 2.0f), 1.0f);
    EXPECT_EQ(minFloat(-5.0f, -2.0f), -5.0f);
    EXPECT_EQ(minFloat(0.0f, 0.0f), 0.0f);
    EXPECT_EQ(minFloat(NAN, 2.0f), 2.0f);
}

TEST(DoubleMinTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(minDouble(1.0, 2.0), 1.0);
    EXPECT_EQ(minDouble(-5.0, -2.0), -5.0);
    EXPECT_EQ(minDouble(0.0, 0.0), 0.0);
    EXPECT_EQ(minDouble(NAN, 2.0), 2.0);
}

TEST(FloatMaxTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(maxFloat(1.0f, 2.0f), 2.0f);
    EXPECT_EQ(maxFloat(-5.0f, -2.0f), -2.0f);
    EXPECT_EQ(maxFloat(0.0f, 0.0f), 0.0f);
    EXPECT_EQ(maxFloat(NAN, 2.0f), 2.0f);
}

TEST(DoubleMaxTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(maxDouble(1.0, 2.0), 2.0);
    EXPECT_EQ(maxDouble(-5.0, -2.0), -2.0);
    EXPECT_EQ(maxDouble(0.0, 0.0), 0.0);
    EXPECT_EQ(maxDouble(NAN, 3.0), 3.0);
}

TEST(FloatClampTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(clampFloat(0.0f, 99845.0f, 3.123123f), 3.123123f);
    EXPECT_EQ(clampFloat(0.0f, 1128331289.0f, -1012.0f), 0.0f);
    EXPECT_EQ(clampFloat(0.0f, 10111.0f, 145800.0f), 10111.0f);
}

TEST(DoubleClampTests, sample_text_cuz_i_dunno) {
    EXPECT_EQ(clampDouble(0.0, 99845.0, 3.123123), 3.123123);
    EXPECT_EQ(clampDouble(0.0, 1128331289.0, -1012.0), 0.0);
    EXPECT_EQ(clampDouble(0.0, 10111.0, 145800.0), 10111.0);
}

TEST(FloatEqualWithPrecisionTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(areFloatsEqualWithPrecision(1.00001f, 1.00002f, 0.0001f));
    EXPECT_FALSE(areFloatsEqualWithPrecision(1.0f, 1.1f, 0.01f));
}

TEST(DoubleEqualWithPrecisionTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(areDoublesEqualWithPrecision(1.00001, 1.00002, 0.0001));
    EXPECT_FALSE(areDoublesEqualWithPrecision(1.0, 1.1, 0.01));
}

TEST(FloatsAreEqualTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(areFloatsEqual(1.0f, 1.0f));
    EXPECT_FALSE(areFloatsEqual(1.0f, 1.1f));
}

TEST(DoublesAreEqualTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(areDoublesEqual(1.0, 1.0));
    EXPECT_FALSE(areDoublesEqual(1.0, 1.1));
}

TEST(FloatIsLessWithPrecisionTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFloatLessWithPrecision(1.0f, 1.0001f, 0.0002f));
    EXPECT_FALSE(isFloatLessWithPrecision(1.0f, 1.00001f, 0.0001f));
}

TEST(DoubleIsLessWithPrecisionTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isDoubleLessWithPrecision(1.0, 1.0001, 0.0002));
    EXPECT_TRUE(isDoubleLessWithPrecision(1.0, 2.0001, .0002));
    EXPECT_FALSE(isDoubleLessWithPrecision(1.0, 1.0000001, 0.000005));
    EXPECT_FALSE(isDoubleLessWithPrecision(5.0, 1.001, 0.0001));
}

TEST(FloatLessTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFloatLess(1.0f, 8761.0123f));
    EXPECT_TRUE(isFloatLess(53.0f, 734.34534534f));
    EXPECT_FALSE(isFloatLess(3.333333f, 1.67f));
}

TEST(DoubleLessTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isDoubleLess(1.0, 6.0));
    EXPECT_FALSE(isDoubleLess(2.123133131313131, 1.0));
}

TEST(FloatIsGreaterWithPrecisionTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFloatGreaterWithPrecision(2.003f, 1.0f, 0.00009f));
    EXPECT_FALSE(isFloatGreaterWithPrecision(10.001f, 1.0f, 0.00567f));
}

TEST(DoubleIsGreatedWithPrecisionTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isDoubleGreaterWithPrecision(2.003, 1.0, 0.000008));
    EXPECT_FALSE(isDoubleGreaterWithPrecision(10.001, 1.0, 0.00089));
}

TEST(FloatIsFloatGreaterTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isFloatGreater(9.12f, 1.0f));
    EXPECT_FALSE(isFloatGreater(1.00023456f, 99.0f));
}

TEST(DoubleIsDoubleGreaterTests, sample_text_cuz_i_dunno) {
    EXPECT_TRUE(isDoubleGreater(37.12312, 1.0));
    EXPECT_FALSE(isDoubleGreater(1.0, 22222225.3223134));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
