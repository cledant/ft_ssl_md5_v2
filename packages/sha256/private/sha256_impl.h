#ifndef SHA256_IMPL_H
#define SHA256_IMPL_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHA256_CHUNK_SIZE 64
#define SHA256_CHUNK_UINT_TAB_SIZE 16
#define SHA256_MAX_LAST_CHUNK 55
#define SHA256_APPEND_BIT 0x80
#define SHA256_HASH_SIZE 64

typedef struct s_sha256_chunk
{
    uint32_t sub_chunk[SHA256_CHUNK_UINT_TAB_SIZE];
} t_sha256_chunk;

typedef struct s_sha256_digest
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
} t_sha256_digest;

// sha256_compute.c
void sha256_compute_digest_from_fd(t_sha256_digest *digest,
                                   int32_t fd,
                                   t_queue *string_chunk);
void sha256_compute_digest_from_str(t_sha256_digest *digest,
                                    uint8_t const *str);

// sha256_utility.c
extern uint32_t const g_sha256_k[64];
t_string *sha256_digest_to_string(t_sha256_digest *digest);

#endif
