#include "ErrorCorrection.h"
#include <iostream>

int main() {
    char* msg = "Hello! I'm Alex";
    ErrorCorrection::chunk* enc = ErrorCorrection::encodeString(msg, 16);
    enc[2] ^= (1ULL << 7); // flip random bits
    enc[1] ^= (1ULL << 5);
    enc[0] ^= (1ULL << 3);
    char* dec = ErrorCorrection::decodeData(enc, 16);

    std::cout << "Original Message: " << msg << std::endl;
    std::cout << "Decoded Message: " << dec << std::endl;
}