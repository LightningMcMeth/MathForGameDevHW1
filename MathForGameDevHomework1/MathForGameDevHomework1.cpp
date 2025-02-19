#include <iostream> //just to test and check values
#include <bit>
#include <bitset>
#include <cinttypes> 

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

//k) Check if floating-point value is signed

bool isFloatSigned(float const value) {
    uint32_t bitValue = FloatToBytes(value);

    return (bitValue >> 31) == 0b1;
}

bool isDoubleSigned(double const value) {
    uint64_t bitValue = DoubleToBytes(value);

    return (bitValue >> 63) == 0b1;
}

//l) Classify floating-point value

//1) Categorizes floating point 
//value num into the following categories: zero, subnormal, normal, infinite, NAN, or implementation-defined category.

enum FPType {
    ZERO,
    SUBNORMAL,
    NORMAL,
    INFINITE,
    NaN,

};


int main()
{
    const float value = 1.2f;
    const float subnormalValue = 1.0e-38f;

    uint32_t convertedValue = FloatToBytes(value);

    const uint32_t bytevalue = 0b00111111100110011001100110011010;
    float convertedBytevalue = BytesToFloat(bytevalue);

    /*
    std::cout << "float value: " << value << std::endl;
    std::cout << "binary form: " << std::bitset<32>(convertedValue) << std::endl;

    std::cout << "float from binary: " << convertedBytevalue << std::endl;
    std::cout << "binary of the float: " << std::bitset<32>(bytevalue) << std::endl;*/

    /*
    std::cout << "is float normal: " << FloatIsNormal(value) << std::endl;
    std::cout << "is float normal: " << FloatIsNormal(INFINITY) << std::endl;
    std::cout << "is float normal: " << FloatIsNormal(NAN) << std::endl;
    std::cout << "is float normal: " << FloatIsNormal(0.0f) << std::endl;*/

    /*
    std::cout << "Is " << value << " subnormal: " << isFloatSubnormal(value) << std::endl;
    std::cout << "Is " << subnormalValue << " subnormal: " << isFloatSubnormal(subnormalValue) << std::endl;
    std::cout << "Is " << INFINITY << " subnormal: " << isFloatSubnormal(INFINITY) << std::endl;*/

    return 0;
}
