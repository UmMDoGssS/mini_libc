/** @file
 * @brief Memory allocation and byte operations.
 *
 * Lengths count bytes. Byte operations with a zero length accept null pointers and access no
 * memory.
 */

#ifndef Mini__MemH_
#define Mini__MemH_

#include "Types.h"
#include "Error.h"

/** @brief Ordering of two byte ranges. */
typedef enum Mini__MemOrder {
    Mini__MemOrder__Less    = -1, /**< The left range comes before the right range. */
    Mini__MemOrder__Equal   = 0,  /**< The ranges contain identical bytes. */
    Mini__MemOrder__Greater = 1,  /**< The left range comes after the right range. */
} Mini__MemOrder;

/**
 * @brief Copies bytes between disjoint ranges.
 * @param[out] destination Writable range of at least @p length bytes.
 * @param[in] source Readable range of at least @p length bytes.
 * @param length Number of bytes to copy.
 */
void Mini__MemCopy(
    Mini__Any *restrict destination,
    const Mini__Any *restrict source,
    Mini__USize length
);

/**
 * @brief Copies bytes between ranges that may overlap.
 * @param[out] destination Writable range of at least @p length bytes.
 * @param[in] source Readable range of at least @p length bytes.
 * @param length Number of bytes to move.
 */
void Mini__MemMove(Mini__Any *destination, const Mini__Any *source, Mini__USize length);

/**
 * @brief Fills a range with a repeated byte.
 * @param[out] destination Writable range of at least @p length bytes.
 * @param value Byte to write.
 * @param length Number of bytes to fill.
 */
void Mini__MemFill(Mini__Any *destination, Mini__Byte value, Mini__USize length);

/**
 * @brief Compares two ranges in unsigned byte order.
 * @param[in] left Readable range of at least @p length bytes.
 * @param[in] right Readable range of at least @p length bytes.
 * @param length Number of bytes in each range.
 * @return The ordering of the first differing bytes, or Mini__MemOrder__Equal if all bytes match
 *         or @p length is zero.
 */
[[nodiscard]]
Mini__MemOrder Mini__MemComp(const Mini__Any *left, const Mini__Any *right, Mini__USize length);

/** @brief Pointer to an allocation, or null for a successful zero-byte request. */
typedef Mini__Any *Mini__MemPtr;

/** @brief Reasons that Mini__MemAlloc can fail. */
typedef enum Mini__MemAllocError {
    Mini__MemAllocError__SizeOverflow, /**< The requested size plus allocator overhead overflows. */
    Mini__MemAllocError__MapFailed,    /**< The OS could not map the requested memory. */
} Mini__MemAllocError;

Mini__DefineRes(Mini__MemPtr, Mini__MemAllocError);

/** @brief Result of Mini__MemAlloc, holding a Mini__MemPtr or a Mini__MemAllocError. */
typedef Mini__Res(Mini__MemPtr, Mini__MemAllocError) Mini__MemAllocRes;

/**
 * @brief Allocates writable memory with 16-byte alignment.
 * @param length Number of bytes to allocate.
 * @return An owned pointer on success or a Mini__MemAllocError on failure. A zero-byte request
 *         succeeds with a null pointer and creates no allocation.
 *
 * The initial contents are unspecified. Release a non-null result with Mini__MemFree.
 */
[[nodiscard]]
Mini__MemAllocRes Mini__MemAlloc(Mini__USize length);

/**
 * @brief Releases memory allocated by Mini__MemAlloc.
 * @param pointer The original pointer to a live allocation, or null to do nothing.
 *
 * The pointer and any pointers into the allocation become invalid after release.
 * If the OS fails to unmap the allocation, this function panics.
 */
void Mini__MemFree(Mini__Any *pointer);

#endif // Mini__MemH_
