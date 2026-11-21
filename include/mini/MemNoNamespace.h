/** @file
 * @brief Short aliases for the memory API in `Mem.h`.
 */

#ifndef Mini__MemNoNamespaceH_
#define Mini__MemNoNamespaceH_

#include "Mem.h"

/** @copydoc Mini__MemOrder */
#define MemOrder Mini__MemOrder
/** @copydoc Mini__MemOrder__Less */
#define MemOrder__Less Mini__MemOrder__Less
/** @copydoc Mini__MemOrder__Equal */
#define MemOrder__Equal Mini__MemOrder__Equal
/** @copydoc Mini__MemOrder__Greater */
#define MemOrder__Greater Mini__MemOrder__Greater

/** @copydoc Mini__MemCopy */
#define MemCopy Mini__MemCopy
/** @copydoc Mini__MemMove */
#define MemMove Mini__MemMove
/** @copydoc Mini__MemFill */
#define MemFill Mini__MemFill
/** @copydoc Mini__MemComp */
#define MemComp Mini__MemComp

/** @copydoc Mini__MemPtr */
#define MemPtr Mini__MemPtr
/** @copydoc Mini__MemAllocError */
#define MemAllocError Mini__MemAllocError
/** @copydoc Mini__MemAllocError__SizeOverflow */
#define MemAllocError__SizeOverflow Mini__MemAllocError__SizeOverflow
/** @copydoc Mini__MemAllocError__MapFailed */
#define MemAllocError__MapFailed Mini__MemAllocError__MapFailed
/** @copydoc Mini__MemAllocRes */
#define MemAllocRes Mini__MemAllocRes

/** @copydoc Mini__MemAlloc */
#define MemAlloc Mini__MemAlloc
/** @copydoc Mini__MemFree */
#define MemFree Mini__MemFree

#endif // Mini__MemNoNamespaceH_
