#include "sha256.h"
#include "sha256_impl.h"

t_string const *
sha256_get_hash(int32_t fd, uint8_t const *str, t_queue *string_chunk)
{
    t_sha256_digest digest = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                               0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

    (void)fd;
    (void)string_chunk;
    if (str) {
        sha256_compute_digest_from_str(&digest, str);
        return (sha256_digest_to_string(&digest));
    }
    return (NULL);
}