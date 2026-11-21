/** @file
 * @brief Scalar and storage types for Linux x86-64.
 */

#ifndef Mini__TypesH_
#define Mini__TypesH_

#include "Macros.h"

// clang-format off: Keep the type aliases aligned.
typedef __INT8_TYPE__   Mini__I8;  /**< Signed 8-bit integer. */
typedef __INT16_TYPE__  Mini__I16; /**< Signed 16-bit integer. */
typedef __INT32_TYPE__  Mini__I32; /**< Signed 32-bit integer. */
typedef __INT64_TYPE__  Mini__I64; /**< Signed 64-bit integer. */

typedef __UINT8_TYPE__  Mini__U8;  /**< Unsigned 8-bit integer. */
typedef __UINT16_TYPE__ Mini__U16; /**< Unsigned 16-bit integer. */
typedef __UINT32_TYPE__ Mini__U32; /**< Unsigned 32-bit integer. */
typedef __UINT64_TYPE__ Mini__U64; /**< Unsigned 64-bit integer. */

typedef __SIZE_TYPE__    Mini__USize; /**< Unsigned type of `sizeof` results. */
typedef __PTRDIFF_TYPE__ Mini__ISize; /**< Signed type of pointer differences. */

typedef __UINTPTR_TYPE__ Mini__UPtr; /**< Unsigned integer type for holding object addresses. */
typedef __INTPTR_TYPE__  Mini__IPtr; /**< Signed integer type for holding object addresses. */

typedef float  Mini__F32; /**< 32-bit floating-point type. */
typedef double Mini__F64; /**< 64-bit floating-point type. */
// clang-format on

static_assert(sizeof(Mini__F32) == 4, "Invalid F32");
static_assert(sizeof(Mini__F64) == 8, "Invalid F64");

/** @brief Alias for `void`. Spell generic object pointers as `Mini__Any *`. */
typedef void Mini__Any;

/** @brief Unsigned character type for accessing object representations byte by byte. */
typedef unsigned char Mini__Byte;

#endif // Mini__TypesH_
