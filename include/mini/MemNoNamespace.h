/** @file
 * @brief Short aliases for the byte operations and ordering in `Mem.h`.
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

#endif // Mini__MemNoNamespaceH_
