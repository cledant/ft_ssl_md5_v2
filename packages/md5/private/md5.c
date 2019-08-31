#include "md5.h"
#include "md5_impl.h"

t_md5_const const g_md5_constants = {
    { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
      5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 },
    { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
      0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
      0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
      0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
      0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
      0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
      0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
      0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
      0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
      0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
      0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 }
};

static inline uint32_t
left_rotate(uint32_t val, uint32_t shift)
{
    return ((val << shift) | (val >> (32 - shift)));
}

t_string *
md5_digest_to_string(t_md5_digest *digest)
{
    static const char base[16] = "0123456789abcdef";

    t_string *hex_digest = t_string_sized_new(MD5_HASH_SIZE + 1);
    if (!hex_digest) {
        return (NULL);
    }
    memset(hex_digest->str, '0', MD5_HASH_SIZE);
    for (uint8_t i = 0; i < 16; ++i) {
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

void
md5_compute_chunk(t_md5_digest *digest, t_md5_chunk const *chunk)
{
    t_md5_digest tmp = *digest;
    uint32_t f = 0;
    uint32_t g = 0;

    for (uint16_t i = 0; i < 64; ++i) {
        if (i <= 15) {
            f = (tmp.b & tmp.c) | ((~tmp.b) & tmp.d);
            g = i;
        } else if (i <= 31) {
            f = (tmp.d & tmp.b) | ((~tmp.d) & tmp.c);
            g = (5 * i + 1) % 16;
        } else if (i <= 47) {
            f = tmp.b ^ tmp.c ^ tmp.d;
            g = (3 * i + 5) % 16;
        } else {
            f = tmp.c ^ (tmp.b | (~tmp.d));
            g = (7 * i) % 16;
        }
        f += tmp.a + g_md5_constants.k[i] + chunk->sub_chunk[g];
        tmp.a = tmp.d;
        tmp.d = tmp.c;
        tmp.c = tmp.b;
        tmp.b += left_rotate(f, g_md5_constants.s[i]);
    }
    digest->a += tmp.a;
    digest->b += tmp.b;
    digest->c += tmp.c;
    digest->d += tmp.d;
}

void
md5_compute_digest_from_str(t_md5_digest *digest, char const *str)
{
    char last_chunk[MD5_CHUNK_SIZE] = { 0 };
    char append_chunk[MD5_CHUNK_SIZE] = { 0 };
    uint64_t len_str = strlen(str);
    uint64_t len_str_bit = len_str * 8;
    uint64_t nb_chunk = len_str / MD5_CHUNK_SIZE;
    uint64_t last_chunk_size = len_str % MD5_CHUNK_SIZE;

    for (uint64_t i = 0; i < nb_chunk; ++i) {
        t_md5_chunk *chunk = (t_md5_chunk *)(str + i * MD5_CHUNK_SIZE);

        md5_compute_chunk(digest, chunk);
    }
    memcpy(last_chunk, str + nb_chunk * MD5_CHUNK_SIZE, last_chunk_size);
    last_chunk[last_chunk_size] = MD5_APPEND_BIT;
    if (!last_chunk_size) {
        memcpy((last_chunk + 56), &len_str_bit, sizeof(uint64_t));
    } else if (last_chunk_size <= MD5_MAX_LAST_CHUNK) {
        memcpy(last_chunk, str + len_str - last_chunk_size, last_chunk_size);
        memcpy(last_chunk + 56, &len_str_bit, sizeof(uint64_t));
    } else {
        memcpy(last_chunk, str + len_str - last_chunk_size, last_chunk_size);
        memcpy(append_chunk + 56, &len_str_bit, sizeof(uint64_t));
    }
    md5_compute_chunk(digest, (t_md5_chunk *)last_chunk);
    if (last_chunk_size > MD5_MAX_LAST_CHUNK) {
        md5_compute_chunk(digest, (t_md5_chunk *)append_chunk);
    }
}

t_string const *
md5_get_hash(int32_t fd, char const *str, t_string_chunk *string_chunk)
{
    (void)string_chunk;
    t_md5_digest digest = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

    if (fd >= 0) {
        // TODO
        return (NULL);
    }
    if (str) {
        md5_compute_digest_from_str(&digest, str);
        return (md5_digest_to_string(&digest));
    }
    return (NULL);
}