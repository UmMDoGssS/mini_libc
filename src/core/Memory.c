#include "mini/Types.h"

// Clang can emit calls to memcpy for aggregate copies in freestanding code.
Mini__Void *memcpy(
    Mini__Void *restrict destination,
    const Mini__Void *restrict source,
    Mini__USize length
) {
    Mini__Byte *destination_bytes = destination;
    const Mini__Byte *source_bytes = source;

    for (Mini__USize index = 0; index < length; ++index) {
        destination_bytes[index] = source_bytes[index];
    }

    return destination;
}
