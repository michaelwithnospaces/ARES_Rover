# 1304173738855875200 1575095055331627144 maps to "Hello, World!\0" for testing
import math

D = 57
P = 6
N = D + P


def decode_chunk(encoded):
    """ Decodes a single Hamming-encoded chunk, correcting errors if necessary. """
    error_pos = 0

    # Check parity bits
    for pIndex in range(P):
        pos = 1 << pIndex  # Position of the parity bit (1-based index)
        parity = 0

        for i in range(1, N + 1):  # 1-based index
            if i & pos:
                if encoded & (1 << (i - 1)):
                    parity ^= 1

        if parity:
            error_pos += pos  # Accumulate the syndrome

    # Correct the error if found
    if error_pos != 0:
        encoded ^= (1 << (error_pos - 1))  # Flip erroneous bit

    # Extract original data bits
    data = 0
    j = 0
    for i in range(N):
        if (i & (i + 1)) != 0:  # Skip parity bit positions
            if encoded & (1 << i):
                data |= (1 << j)
            j += 1

    return data

def to_string(chunks, original_length):
    """ Converts a list of decoded chunks back into a string. """
    num_chunks = math.ceil(original_length / 7)
    result = bytearray(original_length)

    for i in range(num_chunks):
        for j in range(7):
            idx = i * 7 + j
            if idx >= original_length:
                break

            shift = 48 - (j * 8)
            result[idx] = (chunks[i] >> shift) & 0xFF

    return result.decode("utf-8")

def decode_data(encoded_chunks, original_length):
    """ Decodes a list of Hamming-encoded chunks into a string. """
    decoded_chunks = [decode_chunk(chunk) for chunk in encoded_chunks]
    return to_string(decoded_chunks, original_length)