#include "md5.h"
#include "md5_impl.h"

void
md5_display_string_chunk(void *string_chunk, void *data)
{
    (void)data;
    t_byte_array *ba = string_chunk;

    write(1, ba->data, ba->len);
}

t_string const *
md5_get_hash(int32_t fd, uint8_t const *str, t_queue *string_chunk)
{
    t_md5_digest digest = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

    if (fd >= 0) {
        md5_compute_digest_from_fd(&digest, fd, string_chunk);
        return (md5_digest_to_string(&digest));
    }
    if (str) {
        md5_compute_digest_from_str(&digest, str);
        return (md5_digest_to_string(&digest));
    }
    return (NULL);
}