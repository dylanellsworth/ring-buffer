#include <stdlib.h>
#include <stdint.h>

uint32_t set_bit(uint32_t reg, uint8_t pos)
{
    return reg | (1U << pos);
}

uint32_t clear_bit(uint32_t reg, uint8_t pos)
{
    return reg & ~(1U << pos);
}

uint32_t toggle_bit(uint32_t reg, uint8_t pos)
{
    return reg ^ (1U << pos);
}

uint32_t get_bit(uint32_t reg, uint8_t pos)
{
    return (reg & (1U << pos)) != 0;
}

uint32_t lower_mask(uint8_t width)
{
    uint32_t mask = 0U;
    if (width == 0)
    {
        mask = 0U;
    }
    else if (width >= 32)
    {
        mask =  0xFFFFFFFFU;
    }
    else
    {
       mask = 0xFFFFFFFFU >> (32 - width);
    }

    return mask;
}

bool field_valid(uint8_t start, uint8_t width)
{
    bool valid = false;
    if ((width <= 32) && (width > 0) && ((start + width) <= 32)) {
        valid = true;
    }

    return valid;
}

uint32_t insert_bits(uint32_t reg, uint8_t pos, uint8_t width, uint32_t value)
{
    uint32_t updated_reg = reg;

    bool valid = field_valid(pos, width);
    if (valid)
    {
        uint8_t shift = 32 - width - pos;
        uint32_t mask = lower_mask(width) << shift;
        updated_reg = updated_reg & ~(mask);
        updated_reg = updated_reg | (value << shift);
    }
    return updated_reg;
}

uint32_t bit_count(uint32_t reg)
{
    uint32_t count = 0;
    while (reg != 0)
    {
        reg &= (reg-1);
        count++;
    }
    return count;
}
