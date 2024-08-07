#include <stdio.h>
#include <stdint.h>

struct SHA1_Chunk
{
    uint32_t sub_chunk[16];
};

static uint32_t h0 = 0x67452301;
static uint32_t h1 = 0xEFCDAB89;
static uint32_t h2 = 0x98BADCFE;
static uint32_t h3 = 0x10325476;
static uint32_t h4 = 0xC3D2E1F0;

inline uint32_t __leftrot(uint32_t n, uint32_t x)
{
    return (n << x) | (n >> (32 - n)) & ~(-1 << x);
}

int main()
{
    char test[] = "\x0The quick brown fox jumps over the lazy dog";
    uint64_t len = sizeof(test) * (sizeof(char) * 8);

    if(len % 8 == 0)
        test[0] = '1';

}