#include "sha256.h"
#include "sha256_impl.h"

uint32_t const g_sha256_k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static inline void
sha256_digest_endianness(t_sha256_digest *digest)
{
    digest->a = swap_endianness_32(digest->a);
    digest->b = swap_endianness_32(digest->b);
    digest->c = swap_endianness_32(digest->c);
    digest->d = swap_endianness_32(digest->d);
    digest->e = swap_endianness_32(digest->e);
    digest->f = swap_endianness_32(digest->f);
    digest->g = swap_endianness_32(digest->g);
    digest->h = swap_endianness_32(digest->h);
}

t_string *
sha256_digest_to_string(t_sha256_digest *digest)
{
    static const char base[16] = "0123456789abcdef";

    t_string *hex_digest = t_string_sized_new(SHA256_HASH_SIZE + 1);
    if (!hex_digest) {
        return (NULL);
    }
    sha256_digest_endianness(digest);
    memset(hex_digest->str, '0', SHA256_HASH_SIZE);
    for (uint8_t i = 0; i < 32; ++i) {
        uint8_t *num = (uint8_t *)(digest) + i * sizeof(uint8_t);
        uint8_t j = 0;

        while (*num) {
            (hex_digest->str)[i * 2 + 1 - j] = base[*num % 16];
            *num /= 16;
            ++j;
        }
    }
    return (hex_digest);
}