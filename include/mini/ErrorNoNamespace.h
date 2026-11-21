/** @file
 * @brief Short aliases for the panic, result, and option APIs.
 *
 * Include this header to use the short names from `Error.h`.
 */

#ifndef Mini__ErrorNoNamespaceH_
#define Mini__ErrorNoNamespaceH_

#include "Error.h"

/** @copydoc Mini__Panic */
#define Panic Mini__Panic

/** @copydoc Mini__Res */
#define Res Mini__Res
/** @copydoc Mini__ResMth */
#define ResMth Mini__ResMth
/** @copydoc Mini__DefineRes */
#define DefineRes Mini__DefineRes

/** @copydoc Mini__Opt */
#define Opt Mini__Opt
/** @copydoc Mini__OptMth */
#define OptMth Mini__OptMth
/** @copydoc Mini__DefineOpt */
#define DefineOpt Mini__DefineOpt

#endif // Mini__ErrorNoNamespaceH_
