#include "mini/ErrorNoNamespace.h"
#include "mini/MemNoNamespace.h"
#include "mini/TypesNoNamespace.h"
#include "mini/SysNoNamespace.h"

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

typedef struct AllocatedMemHeader {
    alignas(__BIGGEST_ALIGNMENT__) USize length;
} AllocatedMemHeader;

#define IsMmapErr(x) ((UPtr)(x) >= (UPtr)-4095)

MemAllocRes MemAlloc(USize length) {
    if (length == 0) {
        return ResMth(MemPtr, MemAllocError).MakeOk(nullptr);
    }

    if (length > __SIZE_MAX__ - sizeof(AllocatedMemHeader)) {
        return ResMth(MemPtr, MemAllocError).MakeErr(MemAllocError__SizeOverflow);
    }

    USize total_length = length + sizeof(AllocatedMemHeader);

    IPtr pointer = SysMmap(
        nullptr,
        total_length,
        MmapProt__Read | MmapProt__Write,
        MmapFlag__Private | MmapFlag__Anonymous,
        -1,
        0
    );

    if (-4095 <= pointer && pointer < 0) {
        return ResMth(MemPtr, MemAllocError).MakeErr(MemAllocError__MapFailed);
    }

    AllocatedMemHeader *header = (Any *) pointer;
    header->length = total_length;

    return ResMth(MemPtr, MemAllocError).MakeOk(header + 1);
}

void MemFree(Any *pointer) {
    if (!pointer) {
        return;
    }

    AllocatedMemHeader *header = (AllocatedMemHeader *) pointer - 1;
    USize length = header->length;
    I32 result = SysMunmap(header, length);

    if (result != 0) {
        Panic();
    }
}
