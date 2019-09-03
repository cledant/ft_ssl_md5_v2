#include "sha256.h"
#include "sha256_impl.h"

static void
sha256_setup_w(uint32_t *w)
{
    for (size_t i = 0; i < 16; i++)
        w[i] = swap_endianness_32(w[i]);
    for (size_t i = 16; i < 64; i++) {
        uint32_t s0 = right_rotate_32(w[i - 15], 7) ^
                      right_rotate_32(w[i - 15], 18) ^ (w[i - 15] >> 3);
        uint32_t s1 = right_rotate_32(w[i - 2], 17) ^
                      right_rotate_32(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
}

static void
sha256_compute_chunk(t_sha256_digest *digest, t_sha256_chunk *chunk)
{
    uint32_t w[SHA256_CHUNK_SIZE] = { 0 };
    t_sha256_digest tmp = *digest;

    memcpy(w, chunk, SHA256_CHUNK_SIZE);
    sha256_setup_w(w);
    for (size_t i = 0; i < 64; ++i) {
        uint32_t S1 = right_rotate_32(tmp.e, 6) ^ right_rotate_32(tmp.e, 11) ^
                      right_rotate_32(tmp.e, 25);
        uint32_t ch = (tmp.e & tmp.f) ^ ((~tmp.e) & tmp.g);
        uint32_t temp1 = tmp.h + S1 + ch + g_sha256_k[i] + w[i];
        uint32_t S0 = right_rotate_32(tmp.a, 2) ^ right_rotate_32(tmp.a, 13) ^
                      right_rotate_32(tmp.a, 22);
        uint32_t maj = (tmp.a & tmp.b) ^ (tmp.a & tmp.c) ^ (tmp.b & tmp.c);
        uint32_t temp2 = S0 + maj;
        tmp.h = tmp.g;
        tmp.g = tmp.f;
        tmp.f = tmp.e;
        tmp.e = tmp.d + temp1;
        tmp.d = tmp.c;
        tmp.c = tmp.b;
        tmp.b = tmp.a;
        tmp.a = temp1 + temp2;
    }
    digest->a += tmp.a;
    digest->b += tmp.b;
    digest->c += tmp.c;
    digest->d += tmp.d;
    digest->e += tmp.e;
    digest->f += tmp.f;
    digest->g += tmp.g;
    digest->h += tmp.h;
}

static void
sha256_compute_last_chunck(t_sha256_digest *digest,
                           uint64_t total_len,
                           uint8_t const *str,
                           uint64_t len_str,
                           uint64_t offset_str)
{
    uint8_t last_chunk[SHA256_CHUNK_SIZE] = { 0 };
    uint8_t append_chunk[SHA256_CHUNK_SIZE] = { 0 };
    uint64_t len_str_in_bit = swap_endianness_64(total_len * 8);
    uint64_t last_chunk_size = total_len % SHA256_CHUNK_SIZE;

    memcpy(last_chunk, str + offset_str, last_chunk_size);
    last_chunk[last_chunk_size] = SHA256_APPEND_BIT;
    if (!last_chunk_size) {
        memcpy((last_chunk + 56), &len_str_in_bit, sizeof(uint64_t));
    } else if (last_chunk_size <= SHA256_MAX_LAST_CHUNK) {
        memcpy(last_chunk, str + len_str - last_chunk_size, last_chunk_size);
        memcpy(last_chunk + 56, &len_str_in_bit, sizeof(uint64_t));
    } else {
        memcpy(last_chunk, str + len_str - last_chunk_size, last_chunk_size);
        memcpy(append_chunk + 56, &len_str_in_bit, sizeof(uint64_t));
    }
    sha256_compute_chunk(digest, (t_sha256_chunk *)last_chunk);
    if (last_chunk_size > SHA256_MAX_LAST_CHUNK) {
        sha256_compute_chunk(digest, (t_sha256_chunk *)append_chunk);
    }
}

void
sha256_compute_digest_from_fd(t_sha256_digest *digest,
                              int32_t fd,
                              t_queue *string_chunk)
{
    uint8_t read_buff[SHA256_CHUNK_SIZE] = { 0 };
    uint8_t buff[SHA256_CHUNK_SIZE] = { 0 };
    t_byte_array wrapped_buff;
    uint64_t read_char = 0;
    uint64_t total_append_char = 0;

    t_byte_array_init(&wrapped_buff, buff, SHA256_CHUNK_SIZE);
    while ((read_char = read(fd, read_buff, SHA256_CHUNK_SIZE))) {
        uint64_t append_char = 0;

        while (append_char != read_char) {
            t_byte_array_append_no_resize(
              &wrapped_buff, read_buff + append_char, read_char, &append_char);
            total_append_char += append_char;
            if (!t_byte_array_get_free_space(&wrapped_buff)) {
                sha256_compute_chunk(digest,
                                     (t_sha256_chunk *)wrapped_buff.data);
                if (string_chunk) {
                    t_queue_push_back(string_chunk,
                                      t_byte_array_copy(&wrapped_buff));
                }
                t_byte_array_clear(&wrapped_buff);
            }
        }
    }
    if (string_chunk) {
        t_queue_push_back(string_chunk, t_byte_array_copy(&wrapped_buff));
    }
    sha256_compute_last_chunck(
      digest, total_append_char, wrapped_buff.data, wrapped_buff.len, 0);
}

void
sha256_compute_digest_from_str(t_sha256_digest *digest, uint8_t const *str)
{
    uint64_t len_str = strlen((char *)str);
    uint64_t nb_chunk = len_str / SHA256_CHUNK_SIZE;

    for (uint64_t i = 0; i < nb_chunk; ++i) {
        t_sha256_chunk *chunk = (t_sha256_chunk *)(str + i * SHA256_CHUNK_SIZE);

        sha256_compute_chunk(digest, chunk);
    }
    sha256_compute_last_chunck(
      digest, len_str, str, len_str, nb_chunk * SHA256_CHUNK_SIZE);
}