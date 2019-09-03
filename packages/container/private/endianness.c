#include "container.h"

inline uint32_t
swap_endianness_32(uint32_t num)
{
    return (num << 24 | (num << 8 & 0x00FF0000) | (num >> 8 & 0x0000FF00) |
            (num >> 24 & 0x000000FF));
}

inline uint64_t
swap_endianness_64(uint64_t num)
{
    return (num << 56 | (num << 40 & 0x00FF000000000000) |
            (num << 24 & 0x0000FF0000000000) | (num << 8 & 0x000000FF00000000) |
            (num >> 8 & 0x00000000FF000000) | (num >> 24 & 0x0000000000FF0000) |
            (num >> 40 & 0x000000000000FF00) |
            (num >> 56 & 0x00000000000000FF));
}