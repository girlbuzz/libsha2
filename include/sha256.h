#ifndef __SHA256_H
#define __SHA256_H

#include <stddef.h>
#include <inttypes.h>
#include <time.h>

typedef uint32_t SHA256Digest[8];
typedef uint32_t SHA256MessageBlock[16];

/** Perform the full SHA256 algorithm, including preprocessing. The resulting digest is "final" and shouldn't be mutated again.
 * This is best used for a small M that you can fit entirely into memory, this cannot be streamed.
 * @param M Message to hash.
 * @param nbytes Size of M in bytes.
 * @param H Digest to write to.
 */
void sha256(const void *M, size_t nbytes, SHA256Digest H);

#endif /* __SHA256_H */