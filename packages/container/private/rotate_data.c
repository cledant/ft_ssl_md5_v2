#include "container.h"

inline uint32_t
left_rotate_32(uint32_t val, uint32_t shift)
{
    return ((val << shift) | (val >> (32 - shift)));
}

uint32_t
right_rotate_32(uint32_t val, uint32_t shift)
{
    return ((val >> shift) | (val << (32 - shift)));
}