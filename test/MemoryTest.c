#include "mini/TypesNoNamespace.h"

Any *memset(Any *destination, int value, USize length);
Any *memmove(Any *destination, const Any *source, USize length);
int memcmp(const Any *left, const Any *right, USize length);

static bool CheckMemset(void) {
    Byte bytes[] = { 1, 2, 3, 4, 5 };

    return memset(bytes + 1, 0x1a5, 3) == bytes + 1 &&
        memset(bytes + 1, 0, 0) == bytes + 1 &&
        bytes[0] == 1 && bytes[1] == 0xa5 && bytes[2] == 0xa5 &&
        bytes[3] == 0xa5 && bytes[4] == 5;
}

static bool CheckMemmove(void) {
    Byte bytes[] = { 1, 2, 3, 4, 5 };

    if (memmove(bytes + 1, bytes, 4) != bytes + 1 ||
        bytes[0] != 1 || bytes[1] != 1 || bytes[2] != 2 ||
        bytes[3] != 3 || bytes[4] != 4) {
        return false;
    }

    return memmove(bytes, bytes + 1, 4) == bytes &&
        memmove(bytes, bytes, sizeof(bytes)) == bytes &&
        memmove(bytes, bytes + 1, 0) == bytes &&
        bytes[0] == 1 && bytes[1] == 2 && bytes[2] == 3 &&
        bytes[3] == 4 && bytes[4] == 4;
}

static bool CheckMemcmp(void) {
    const Byte left[] = { 3, 0x80, 0 };
    const Byte right[] = { 3, 0x7f, 255 };

    return memcmp(left, right, 0) == 0 &&
        memcmp(left, right, 1) == 0 &&
        memcmp(left, left, sizeof(left)) == 0 &&
        memcmp(left, right, sizeof(left)) > 0 &&
        memcmp(right, left, sizeof(right)) < 0;
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

    return 0;
}
