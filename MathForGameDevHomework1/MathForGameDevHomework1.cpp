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

/*
bool isfiniteFloat(float const& value) {

}

bool isfiniteDouble(double const& value) {

}*/

//b) Check if floating-point value is any infinity value

//c) Check if floating-point value is positive infinity value

//c) Check if floating-point value is positive infinity value

//d) Check if floating-point value is negative infinity value

//e) Check if floating-point value is any zero value

//f) Check if floating-point value is positive zero value

//g) Check if floating-point value is negative zero value

//h) Check if floating-point value is not a number value

//i) Check if floating-point value is normal value

bool FloatIsNormal(float const value) {
    uint32_t bitValue = FloatToBytes(value);
    uint8_t exponent = bitValue >> 23;

    return (exponent >= 0b00000001) && (exponent <= 0b11111110);
}

bool DoubleIsNormal(double const value) {
    uint32_t bitValue = FloatToBytes(value);
    uint8_t exponent = bitValue >> 52;

    return (exponent >= 0b00000001) && (exponent <= 0b11111110);
}

//j) Check if floating-point value is subnormal value

bool FloatIsSubnormal(float const& value) {
    uint32_t bitValue = FloatToBytes(value);
    uint8_t exponent = bitValue >> 23;
    uint32_t mantissa = bitValue & 0b1111111111111111111111;

    return (exponent == 0b00000000) && (mantissa != 0b00000000);
}

//k) Check if floating-point value is signed

//l) Classify floating-point value


int main()
{
    const float value = 1.2f;
    uint32_t convertedValue = FloatToBytes(value);

    const uint32_t bytevalue = 0b00111111100110011001100110011010;
    float convertedBytevalue = BytesToFloat(bytevalue);

    /*
    std::cout << "float value: " << value << std::endl;
    std::cout << "binary form: " << std::bitset<32>(convertedValue) << std::endl;

    std::cout << "reconstructed float from binary: " << convertedBytevalue << std::endl;
    std::cout << "binary representation: " << std::bitset<32>(bytevalue) << std::endl;*/

    /*
    std::cout << "is float normal: " << FloatIsNormal(value) << std::endl;
    std::cout << "is float normal: " << FloatIsNormal(INFINITY) << std::endl;
    std::cout << "is float normal: " << FloatIsNormal(NAN) << std::endl;
    std::cout << "is float normal: " << FloatIsNormal(0.0f) << std::endl;*/


    return 0;
}
