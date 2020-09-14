/**
 * @file include/ghost/types.h.
 * 
 * `include/ghost/types.h` defines types used by Ghost but not exposed by the
 * freestanding C headers, such as `ssize_t`.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#ifndef GHOST_TYPES_H_
#define GHOST_TYPES_H_

#include <stdint.h>

/**
 * @typedef ssize_t
 *
 * Signed integer of the CPU's word length.
 */
#if UINT8_MAX == SIZE_MAX
typedef int8_t ssize_t;
#elif UINT16_MAX == SIZE_MAX
typedef int16_t ssize_t;
#elif UINT32_MAX == SIZE_MAX
typedef int32_t ssize_t;
#elif UINT64_MAX == SIZE_MAX
typedef int64_t ssize_t;
#endif

#endif
