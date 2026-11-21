#include "mini/TypesNoNamespace.h"

// Memory entry points for the freestanding Clang runtime.

Any *memcpy(
    Any *restrict destination,
    const Any *restrict source,
    USize length
) {
    Byte *destination_bytes = destination;
    const Byte *source_bytes = source;

    for (USize index = 0; index < length; ++index) {
        destination_bytes[index] = source_bytes[index];
    }

    return destination;
}

Any *memset(Any *destination, int value, USize length) {
    Byte *destination_bytes = destination;
    const Byte fill = (Byte) value;

    for (USize index = 0; index < length; ++index) {
        destination_bytes[index] = fill;
    }

    return destination;
}

Any *memmove(Any *destination, const Any *source, USize length) {
    Byte *destination_bytes = destination;
    const Byte *source_bytes = source;

    // Order addresses as integers, including when the buffers are in separate objects.
    const UPtr destination_address = (UPtr) destination;
    const UPtr source_address = (UPtr) source;

    if (destination_address < source_address) {
        for (USize index = 0; index < length; ++index) {
            destination_bytes[index] = source_bytes[index];
        }
    } else if (destination_address > source_address) {
        for (USize index = length; index != 0; --index) {
            destination_bytes[index - 1] = source_bytes[index - 1];
        }
    }

    return destination;
}

int memcmp(const Any *left, const Any *right, USize length) {
    const Byte *left_bytes = left;
    const Byte *right_bytes = right;

    for (USize index = 0; index < length; ++index) {
        if (left_bytes[index] != right_bytes[index]) {
            return left_bytes[index] - right_bytes[index];
        }
    }

    return 0;
}
