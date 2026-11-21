#include "mini/MemNoNamespace.h"
#include "mini/TypesNoNamespace.h"

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

    return 0;
}
