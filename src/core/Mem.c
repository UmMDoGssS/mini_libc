#include "mini/MemNoNamespace.h"
#include "mini/TypesNoNamespace.h"

// Memory entry points for the freestanding Clang runtime.

Any *memcpy(Any *restrict destination, const Any *restrict source, USize length) {
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

void MemCopy(Any *restrict destination, const Any *restrict source, USize length) {
    if (length != 0) {
        memcpy(destination, source, length);
    }
}

void MemMove(Any *destination, const Any *source, USize length) {
    if (length != 0) {
        memmove(destination, source, length);
    }
}

void MemFill(Any *destination, Byte value, USize length) {
    if (length != 0) {
        memset(destination, value, length);
    }
}

MemOrder MemComp(const Any *left, const Any *right, USize length) {
    if (length == 0) {
        return MemOrder__Equal;
    }

    const int order = memcmp(left, right, length);
    if (order < 0) {
        return MemOrder__Less;
    }
    return order == 0 ? MemOrder__Equal : MemOrder__Greater;
}
