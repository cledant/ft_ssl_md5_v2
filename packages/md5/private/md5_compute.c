#include "md5.h"
#include "md5_impl.h"

static inline uint32_t
left_rotate(uint32_t val, uint32_t shift)
{
    return ((val << shift) | (val >> (32 - shift)));
}

static void
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

static void
md5_compute_last_chunck(t_md5_digest *digest,
                        uint64_t total_len,
                        uint8_t const *str,
                        uint64_t len_str,
                        uint64_t offset_str)
{
    uint8_t last_chunk[MD5_CHUNK_SIZE] = { 0 };
    uint8_t append_chunk[MD5_CHUNK_SIZE] = { 0 };
    uint64_t len_str_in_bit = total_len * 8;
    uint64_t last_chunk_size = total_len % MD5_CHUNK_SIZE;

    memcpy(last_chunk, str + offset_str, last_chunk_size);
    last_chunk[last_chunk_size] = MD5_APPEND_BIT;
    if (!last_chunk_size) {
        memcpy((last_chunk + 56), &len_str_in_bit, sizeof(uint64_t));
    } else if (last_chunk_size <= MD5_MAX_LAST_CHUNK) {
        memcpy(last_chunk, str + len_str - last_chunk_size, last_chunk_size);
        memcpy(last_chunk + 56, &len_str_in_bit, sizeof(uint64_t));
    } else {
        memcpy(last_chunk, str + len_str - last_chunk_size, last_chunk_size);
        memcpy(append_chunk + 56, &len_str_in_bit, sizeof(uint64_t));
    }
    md5_compute_chunk(digest, (t_md5_chunk *)last_chunk);
    if (last_chunk_size > MD5_MAX_LAST_CHUNK) {
        md5_compute_chunk(digest, (t_md5_chunk *)append_chunk);
    }
}

void
md5_compute_digest_from_fd(t_md5_digest *digest,
                           int32_t fd,
                           t_queue *string_chunk)
{
    uint8_t read_buff[MD5_CHUNK_SIZE] = { 0 };
    uint8_t buff[MD5_CHUNK_SIZE] = { 0 };
    t_byte_array wrapped_buff;
    uint64_t read_char = 0;
    uint64_t total_append_char = 0;

    t_byte_array_init(&wrapped_buff, buff, MD5_CHUNK_SIZE);
    while ((read_char = read(fd, read_buff, MD5_CHUNK_SIZE))) {
        uint64_t append_char = 0;

        while (append_char != read_char) {
            t_byte_array_append_no_resize(
              &wrapped_buff, read_buff + append_char, read_char, &append_char);
            total_append_char += append_char;
            if (!t_byte_array_get_free_space(&wrapped_buff)) {
                md5_compute_chunk(digest, (t_md5_chunk *)wrapped_buff.data);
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
    md5_compute_last_chunck(
      digest, total_append_char, wrapped_buff.data, wrapped_buff.len, 0);
}

void
md5_compute_digest_from_str(t_md5_digest *digest, uint8_t const *str)
{
    uint64_t len_str = strlen((char *)str);
    uint64_t nb_chunk = len_str / MD5_CHUNK_SIZE;

    for (uint64_t i = 0; i < nb_chunk; ++i) {
        t_md5_chunk *chunk = (t_md5_chunk *)(str + i * MD5_CHUNK_SIZE);

        md5_compute_chunk(digest, chunk);
    }
    md5_compute_last_chunck(
      digest, len_str, str, len_str, nb_chunk * MD5_CHUNK_SIZE);
}