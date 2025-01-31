typedef unsigned char byte;
typedef bool bit;

#include <cmath>

#include <iostream>
using std::cout, std::endl;

bit* convertChar(char s) {
    bit* res = new bit[8];

    for (int i = 0; i < 8; ++i) {
        res[7 - i] = (s >> i) & 1; 
    }

    return res;
}

char revertChar(bit* s) {
    char result = 0;

    for (int i = 0; i < 8; ++i) {
        result |= (s[i] << (7 - i));  // Set each bit in the char
    }
    
    return result;
}

bit* convertString(char* s, size_t length) {
    bit* res = new bit[length * 8];

    for (int i = 0; i < length; i++) {
        bit* data = convertChar(s[i]);

        for (int j = 0; j < 8; j++) {
            int h = i * 8 + j;
            res[h] = data[j];
        }

        delete[] data;
    }

    return res;
}

char* revertString(bit* s, int d) {
    char* res = new char[d / 8];

    for (int i = 0; i < d / 8; i++) {
        bit* b = new bit[8];

        for (int j = 0; j < 8; j++) {
            b[j] = s[i * 8 + j];
        }

        res[i] = revertChar(b);
        delete[] b;
    }

    return res;
}

int numParity(int d) {
    int p = 1; // number of parity bits

    // Find the number of parity bits needed
    while ((1 << p) < d + p + 1) { // inequality gives number of parity bits, increment until true
        p += 1;
    }
    return p;
}

bit* encode(bit* bits, int d) {
    int p = numParity(d);

    int n = p + d;
    bit* out = new bit[n]; // output array

    // Inserts data into new array, skipping bits numbered by powers of two (these are parity bits)
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if ((i & (i + 1)) != 0)  { // checks if power of two, if not, puts in data
            out[i] = bits[j];
            ++j;
        }
    }

    // Compute parity bits
    for (int pIndex = 0; pIndex < p; pIndex++) {
        int pos = 1 << pIndex; // 2 ^ pIndex, index of current parity bit
        int parity = 0;

        for (int i = 1; i < n + 1; ++i) { // for each bit in the message
            if (((i) & pos) != 0) { // if the bit is part of what this parity bit checks
                // xors parity with value, -1 because hamming algorithm is 1-indexed
                parity ^= out[i - 1];
            }
        }

        out[pos - 1] = parity; // sets parity bit to parity of bits it checks
    }

    return out;
}

bit* decode(bit* bits, int d) {
    int p = numParity(d);
    int n = p + d;
    cout << "Received by decoder: ";
    for (int i = 0; i < n; ++i) {
        cout << bits[i];
    }
    cout << endl;


    int syndrome = 0;
    // Rechecks parity bits like shown above
    for (int pIndex = 0; pIndex < p; ++pIndex) {
        int pos = 1 << pIndex;
        int parity = 0;

        for (int i = 1; i < n + 1; ++i) {
            if (((i) & pos) != 0) {
                // cout << "parity bit " << pIndex << " at position " << pos << " affected by bit " << i - 1 << " with value " << out[i - 1] << endl;
                parity ^= bits[i - 1];
            }
        }

        if (parity) { // If the parity is 1 (shouldn't be), add to syndrome
            syndrome += pos;
        }
    }

    // Nonzero syndrome means error detected, if there's just 1 error it will be at the position denoted by the syndrome
    if (syndrome > 0 && syndrome <= n) {
        bits[syndrome - 1] ^= 1; // Flip the bit to fix it
        cout << "Error corrected at bit " << syndrome - 1 << endl;
    }

    // Now extract the data bits (skip power of two indices)
    int j = 0;
    bit* res = new bit[d];
    for (int i = 1; i < n; i++) {
        if ((i & (i + 1)) == 0) {
            continue;
        } else {
            res[j] = bits[i];
            j++;
        }
    }

    return res;
}

int main() {
    char* str = "hello";
    bit* bytes = convertString(str, 6);
    bit* enc = encode(bytes, 48);
    bit* dec = decode(enc, 48);
    char* res = revertString(dec, 48);
    cout << res << endl;
}