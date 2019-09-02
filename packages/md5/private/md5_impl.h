#ifndef MD5_IMPL_H
#define MD5_IMPL_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MD5_CHUNK_SIZE 64
#define MD5_HASH_SIZE 32
#define MD5_CHUNK_UINT_TAB_SIZE 16
#define MD5_MAX_LAST_CHUNK 55
#define MD5_APPEND_BIT 0x80

/*
**	Structure containing constants value :
**		s = shifts
**		k[i] = floor(2^32 + abs(sin(i + 1)))
*/
typedef struct s_md5_const
{
    uint32_t s[64];
    uint32_t k[64];
} t_md5_const;

extern t_md5_const const g_md5_constants;

typedef struct s_md5_digest
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
} t_md5_digest;

typedef struct s_md5_chunk
{
    uint32_t sub_chunk[MD5_CHUNK_UINT_TAB_SIZE];
} t_md5_chunk;

// md5_compute.c
void md5_compute_digest_from_fd(t_md5_digest *digest,
                                int32_t fd,
                                t_queue *string_chunk);
void md5_compute_digest_from_str(t_md5_digest *digest, uint8_t const *str);

// md5_utility.c
t_string *md5_digest_to_string(t_md5_digest *digest);

#endif
