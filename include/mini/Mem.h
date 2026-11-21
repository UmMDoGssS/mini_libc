/** @file
 * @brief Byte operations on caller-provided memory.
 *
 * Lengths count bytes. At zero length, pointers may be null and no memory is accessed.
 */

#ifndef Mini__MemH_
#define Mini__MemH_

#include "Types.h"

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

#endif // Mini__MemH_
