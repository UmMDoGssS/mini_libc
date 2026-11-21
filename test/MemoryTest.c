#include "mini/ErrorNoNamespace.h"
#include "mini/MemNoNamespace.h"
#include "mini/TypesNoNamespace.h"
#include "platform/linux/x86_64/Syscall.h"

Any *memset(Any *destination, int value, USize length);
Any *memmove(Any *destination, const Any *source, USize length);
int memcmp(const Any *left, const Any *right, USize length);

static bool CheckMemset(void) {
    Byte bytes[] = { 1, 2, 3, 4, 5 };

    return memset(bytes + 1, 0x1a5, 3) == bytes + 1 && memset(bytes + 1, 0, 0) == bytes + 1 &&
        bytes[0] == 1 && bytes[1] == 0xa5 && bytes[2] == 0xa5 && bytes[3] == 0xa5 && bytes[4] == 5;
}

static bool CheckMemmove(void) {
    Byte bytes[] = { 1, 2, 3, 4, 5 };

    if (memmove(bytes + 1, bytes, 4) != bytes + 1 || bytes[0] != 1 || bytes[1] != 1 ||
        bytes[2] != 2 || bytes[3] != 3 || bytes[4] != 4) {
        return false;
    }

    return memmove(bytes, bytes + 1, 4) == bytes && memmove(bytes, bytes, sizeof(bytes)) == bytes &&
        memmove(bytes, bytes + 1, 0) == bytes && bytes[0] == 1 && bytes[1] == 2 && bytes[2] == 3 &&
        bytes[3] == 4 && bytes[4] == 4;
}

static bool CheckMemcmp(void) {
    const Byte left[] = { 3, 0x80, 0 };
    const Byte right[] = { 3, 0x7f, 255 };

    return memcmp(left, right, 0) == 0 && memcmp(left, right, 1) == 0 &&
        memcmp(left, left, sizeof(left)) == 0 && memcmp(left, right, sizeof(left)) > 0 &&
        memcmp(right, left, sizeof(right)) < 0;
}

static bool CheckMemCopy(void) {
    const Byte source[] = { 0, 0x80, 0xff, 0 };
    Byte destination[] = { 1, 2, 3, 4 };

    MemCopy(destination + 1, source + 1, 2);

    return destination[0] == 1 && destination[1] == 0x80 && destination[2] == 0xff &&
        destination[3] == 4;
}

static bool CheckMemMove(void) {
    Byte bytes[] = { 0xaa, 1, 2, 3, 4, 0xbb };
    const Byte after_right[] = { 0xaa, 1, 1, 2, 3, 0xbb };
    const Byte after_left[] = { 0xaa, 1, 2, 3, 3, 0xbb };

    MemMove(bytes + 2, bytes + 1, 3);
    if (memcmp(bytes, after_right, sizeof(bytes)) != 0) {
        return false;
    }

    MemMove(bytes + 1, bytes + 2, 3);
    if (memcmp(bytes, after_left, sizeof(bytes)) != 0) {
        return false;
    }

    MemMove(bytes, bytes, sizeof(bytes));
    return memcmp(bytes, after_left, sizeof(bytes)) == 0;
}

static bool CheckMemFill(void) {
    Byte bytes[] = { 1, 2, 3, 4, 5 };

    MemFill(bytes + 1, 0xa5, 3);
    if (bytes[0] != 1 || bytes[1] != 0xa5 || bytes[2] != 0xa5 || bytes[3] != 0xa5 ||
        bytes[4] != 5) {
        return false;
    }

    MemFill(bytes + 2, 0, 1);
    return bytes[0] == 1 && bytes[1] == 0xa5 && bytes[2] == 0 && bytes[3] == 0xa5 && bytes[4] == 5;
}

static bool CheckMemComp(void) {
    const Byte left[] = { 3, 0x80, 0 };
    const Byte right[] = { 3, 0x7f, 255 };
    const Byte equal[] = { 3, 0x80, 0 };

    const MemOrder order = MemComp(left, right, sizeof(left));
    return order == MemOrder__Greater && MemComp(right, left, sizeof(left)) == MemOrder__Less &&
        MemComp(left, equal, sizeof(left)) == MemOrder__Equal &&
        MemComp(left, right, 1) == MemOrder__Equal;
}

static bool CheckEmptyRange(void) {
    Byte byte = 42;

    MemCopy(nullptr, nullptr, 0);
    MemMove(nullptr, nullptr, 0);
    MemFill(nullptr, 0xff, 0);
    MemCopy(&byte, nullptr, 0);
    MemMove(&byte, nullptr, 0);
    MemFill(&byte, 0xff, 0);

    return byte == 42 && MemComp(nullptr, nullptr, 0) == MemOrder__Equal;
}

static bool CheckZeroSizeAlloc(void) {
    const MemAllocRes result = MemAlloc(0);
    const MemPtr *pointer = ResMth(MemPtr, MemAllocError).GetOk(&result);

    MemFree(nullptr);
    return pointer != nullptr && *pointer == nullptr;
}

static bool CheckMemAllocErrors(void) {
    const MemAllocRes overflow = MemAlloc(__SIZE_MAX__);
    const MemAllocError *error = ResMth(MemPtr, MemAllocError).GetErr(&overflow);
    if (error == nullptr || *error != MemAllocError__SizeOverflow) {
        return false;
    }

    // This length fits in USize but exceeds the Linux x86-64 userspace address space.
    const MemAllocRes map_failure = MemAlloc((USize) 1 << 60);
    error = ResMth(MemPtr, MemAllocError).GetErr(&map_failure);
    return error != nullptr && *error == MemAllocError__MapFailed;
}

enum { PageSize = 4096, AllocAlignment = 16, OutOfMemory = 12 };

static bool IsUnmapped(UPtr address) {
    const IPtr page = (IPtr) (address - address % PageSize);
    U8 residency;
    return Syscall6(SyscallNumber__Mincore, page, PageSize, (IPtr) &residency, 0, 0, 0) ==
        -OutOfMemory;
}

static bool CheckMemAlloc(void) {
    const USize length = PageSize + 1;
    const MemAllocRes small = MemAlloc(1);
    const MemAllocRes large = MemAlloc(length);
    const MemPtr *small_pointer = ResMth(MemPtr, MemAllocError).GetOk(&small);
    const MemPtr *large_pointer = ResMth(MemPtr, MemAllocError).GetOk(&large);
    if (small_pointer == nullptr || *small_pointer == nullptr || large_pointer == nullptr ||
        *large_pointer == nullptr) {
        return false;
    }

    const UPtr small_address = (UPtr) *small_pointer;
    const UPtr large_address = (UPtr) *large_pointer;
    if (small_address % AllocAlignment != 0 || large_address % AllocAlignment != 0) {
        return false;
    }

    volatile Byte *small_bytes = *small_pointer;
    volatile Byte *large_bytes = *large_pointer;
    small_bytes[0] = 17;
    large_bytes[0] = 39;
    large_bytes[length - 1] = 73;
    if (large_bytes[0] != 39 || large_bytes[length - 1] != 73) {
        return false;
    }

    MemFree(*large_pointer);
    if (!IsUnmapped(large_address) || !IsUnmapped(large_address + length - 1) ||
        small_bytes[0] != 17) {
        return false;
    }

    MemFree(*small_pointer);
    return IsUnmapped(small_address);
}

int Main(void) {
    if (!CheckMemset()) {
        return 1;
    }
    if (!CheckMemmove()) {
        return 2;
    }
    if (!CheckMemcmp()) {
        return 3;
    }
    if (!CheckMemCopy()) {
        return 4;
    }
    if (!CheckMemMove()) {
        return 5;
    }
    if (!CheckMemFill()) {
        return 6;
    }
    if (!CheckMemComp()) {
        return 7;
    }
    if (!CheckEmptyRange()) {
        return 8;
    }
    if (!CheckZeroSizeAlloc()) {
        return 9;
    }
    if (!CheckMemAllocErrors()) {
        return 10;
    }
    if (!CheckMemAlloc()) {
        return 11;
    }

    return 0;
}
