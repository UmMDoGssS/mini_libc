#include "mini/TypesNoNamespace.h"

// Clang can emit calls to memcpy for aggregate copies in freestanding code.
Void *memcpy(
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
