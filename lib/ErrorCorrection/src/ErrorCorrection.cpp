#include "ErrorCorrection.h"
#include <cmath>

/** 64 bits (8 bytes) of data */
typedef unsigned long long chunk;

/**
 * Converts a char array s to a chunk array given the length of s
 * Ensure the returned chunk array is deleted after use
 */
chunk* ErrorCorrection::fromString(char* s, int len) {
    int n = ceil((double)len / 7.0);
    chunk* arr = new chunk[n];

    // cycle through complete chunks
    for (int i = 0; i < n; i++) {
        chunk res = 0;
        for (int j = 0; j < 7; j++) {
            if (i * 7 + j >= len) {
                break;
            }

            int shift = 48 - (j * 8);
            res |= (static_cast<chunk>(s[i * 7 + j]) << shift);
        }
        arr[i] = res;
    }

    return arr;
}

/**
 * Converts a chunk array s to a char array given the length of the char array
 * Ensure the returned char array is deleted after use
 */
char* ErrorCorrection::toString(chunk* data, int originalLength) {
    size_t len = ceil((double)originalLength / 7.0);
    // Allocate buffer for original string (+1 for null terminator)
    char* s = new char[originalLength];

    // Extract characters from chunks
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < 7; j++) {
            size_t idx = i * 7 + j;
            if (idx >= originalLength) {
                break; // Stop once we reach original length
            }

            int shift = 48 - (j * 8);
            s[idx] = static_cast<char>((data[i] >> shift) & 0xFF);
        }
    }

    return s;
}

/**
 * Encodes a single chunk of data
 */
chunk ErrorCorrection::encode(chunk data) {
    char d = 57; // Number of data bits
    char p = 6;
    char n = d + p; // Total number of bits (63)

    chunk encoded = 0;

    int j = 0;
    // Insert data bits into the encoded value, skipping parity positions
    for (int i = 0; i < n; ++i) {
        if ((i & (i + 1)) != 0) { // Skip parity positions (powers of 2)
            if (data & (1ULL << j)) {
                encoded |= (1ULL << i); // Copy data bit
            }
            j++;
        }
    }

    // Compute parity bits
    for (int pIndex = 0; pIndex < p; ++pIndex) {
        int pos = 1 << pIndex; // 2^pIndex, position of the parity bit
        int parity = 0;

        for (int i = 1; i <= n; ++i) { // 1-based index
            if (i & pos) { // If this bit contributes to this parity check
                if (encoded & (1ULL << (i - 1))) {
                    parity ^= 1; // XOR to compute parity
                }
            }
        }

        if (parity) {
            encoded |= (1ULL << (pos - 1)); // Set parity bit
        }
    }

    return encoded;
}

/**
 * Decodes a single chunk, correcting errors as necessary
 */
chunk ErrorCorrection::decode(chunk &encoded) {
    constexpr int d = 57;
    constexpr int p = 6;
    constexpr int n = d + p;

    int error_pos = 0;

    // Check parity bits using same procedure as before
    for (int pIndex = 0; pIndex < p; ++pIndex) {
        int pos = 1 << pIndex;
        int parity = 0;

        for (int i = 1; i <= n; ++i) {
            if (i & pos) {
                if (encoded & (1ULL << (i - 1))) {
                    parity ^= 1;
                }
            }
        }

        if (parity) { // if bit is wrong, add to syndrome (error position)
            error_pos += pos;
        }
    }

    // Correct the error if detected
    if (error_pos != 0) {
        // cout << "Error detected at position " << error_pos << endl;
        encoded ^= (1ULL << (error_pos - 1)); // Flip erroneous bit
    } else {
        // cout << "No errors detected." << endl;
    }

    // Extract original data
    chunk data = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if ((i & (i + 1)) != 0) { // Skip parity bits
            if (encoded & (1ULL << i)) {
                data |= (1ULL << j);
            }
            j++;
        }
    }

    return data;
}

/**
 * Takes in a char array s and its length and returns a dynamically allocated array of Hamming-encoded chunks (ULLs)
 * Make sure encoded chunks are deleted after use
 */
chunk* ErrorCorrection::encodeString(char* s, int len) {
    chunk* data = ErrorCorrection::fromString(s, len);
    int n = ceil((double)len / 7.0);

    for (int i = 0; i < n; ++i) {
        data[i] = ErrorCorrection::encode(data[i]);
    }

    return data;
}

/**
 * Takes in an encoded array of Hamming-encoded chunks and the length of the encoded string and returns the decoded string,
 * correcting errors as possible
 * Make sure decoded string is deleted after use.
 */
char* ErrorCorrection::decodeData(chunk* data, int len) {
    int n = ceil((double)len / 7.0);


    for (int i = 0; i < n; ++i) {
        data[i] = ErrorCorrection::decode(data[i]);
    }

    char* str = ErrorCorrection::toString(data, len);
    return str;
}
