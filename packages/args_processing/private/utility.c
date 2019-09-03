#include "args_processing.h"
#include "args_processing_impl.h"

void
display_string_chunk(void *string_chunk, void *data)
{
    (void)data;
    t_byte_array *ba = string_chunk;

    write(1, ba->data, ba->len);
}