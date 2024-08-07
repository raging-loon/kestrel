#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))
#define ROTL(x, n) ((x << n) | (x >> (32 - n)) & ~((-1 << n)))
#define MD5STEP(f, w, x, y, z, data, s) w = ROTL(w + f(x, y, z) + data, s) + x

static const int __md5_shifts[64] =
{
 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, 
 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 
 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 
 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 
};

static const uint32_t __md5_table[64] =
{
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 
};

static const uint8_t __ldu_md5_padding[] =
{
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

typedef struct
{
    uint32_t states[4];
    uint32_t count[2];
    unsigned char digest[64];
} LDU_MD5_CTX;


void LDU_MD5(const char * input, char* output)
{
    LDU_MD5_CTX ctx;
    LDU_MD5_Init(&ctx);

}

void LDU_MD5_Init(LDU_MD5_CTX * ctx)
{
    ctx->states[0] = 0x67452301;
    ctx->states[1] = 0xefcdab89;
    ctx->states[2] = 0x98badcfe;
    ctx->states[3] = 0x10325476;

    memset(ctx->count, 0, sizeof(ctx->digest) + sizeof(ctx->count));
}

void LDU_MD5_Update(LDU_MD5_CTX* ctx, uint8_t* input, size_t inlen)
{
    for(size_t i = 0; i < inlen; i++)
    {
    }
}

void LDU_MD5_Transform(char* hash, const char* data, uint32_t inlen)
{
    LDU_MD5_CTX ctx;

    ldu_md5_init(&ctx);

    uint32_t a = 0x67452301;
    uint32_t b = 0xefcdab89;
    uint32_t c = 0x98badcfe;
    uint32_t d = 0x10325476;

    MD5STEP(F1, a, b, c, d, data[0] + 0xd76aa478, 7);
    MD5STEP(F1, d, a, b, c, data[1] + 0xe8c7b756, 12);
    MD5STEP(F1, c, d, a, b, data[2] + 0x242070db, 17);
    MD5STEP(F1, b, c, d, a, data[3] + 0xc1bdceee, 22);
    MD5STEP(F1, a, b, c, d, data[4] + 0xf57c0faf, 7);
    MD5STEP(F1, d, a, b, c, data[5] + 0x4787c62a, 12);
    MD5STEP(F1, c, d, a, b, data[6] + 0xa8304613, 17);
    MD5STEP(F1, b, c, d, a, data[7] + 0xfd469501, 22);
    MD5STEP(F1, a, b, c, d, data[8] + 0x698098d8, 7);
    MD5STEP(F1, d, a, b, c, data[9] + 0x8b44f7af, 12);
    MD5STEP(F1, c, d, a, b, data[10] + 0xffff5bb1, 17);
    MD5STEP(F1, b, c, d, a, data[11] + 0x895cd7be, 22);
    MD5STEP(F1, a, b, c, d, data[12] + 0x6b901122, 7);
    MD5STEP(F1, d, a, b, c, data[13] + 0xfd987193, 12);
    MD5STEP(F1, c, d, a, b, data[14] + 0xa679438e, 17);
    MD5STEP(F1, b, c, d, a, data[15] + 0x49b40821, 22);

    MD5STEP(F2, a, b, c, d, data[1] + 0xf61e2562, 5);
    MD5STEP(F2, d, a, b, c, data[6] + 0xc040b340, 9);
    MD5STEP(F2, c, d, a, b, data[11] + 0x265e5a51, 14);
    MD5STEP(F2, b, c, d, a, data[0] + 0xe9b6c7aa, 20);
    MD5STEP(F2, a, b, c, d, data[5] + 0xd62f105d, 5);
    MD5STEP(F2, d, a, b, c, data[10] + 0x02441453, 9);
    MD5STEP(F2, c, d, a, b, data[15] + 0xd8a1e681, 14);
    MD5STEP(F2, b, c, d, a, data[4] + 0xe7d3fbc8, 20);
    MD5STEP(F2, a, b, c, d, data[9] + 0x21e1cde6, 5);
    MD5STEP(F2, d, a, b, c, data[14] + 0xc33707d6, 9);
    MD5STEP(F2, c, d, a, b, data[3] + 0xf4d50d87, 14);
    MD5STEP(F2, b, c, d, a, data[8] + 0x455a14ed, 20);
    MD5STEP(F2, a, b, c, d, data[13] + 0xa9e3e905, 5);
    MD5STEP(F2, d, a, b, c, data[2] + 0xfcefa3f8, 9);
    MD5STEP(F2, c, d, a, b, data[7] + 0x676f02d9, 14);
    MD5STEP(F2, b, c, d, a, data[12] + 0x8d2a4c8a, 20);

    MD5STEP(F3, a, b, c, d, data[5] + 0xfffa3942, 4);
    MD5STEP(F3, d, a, b, c, data[8] + 0x8771f681, 11);
    MD5STEP(F3, c, d, a, b, data[11] + 0x6d9d6122, 16);
    MD5STEP(F3, b, c, d, a, data[14] + 0xfde5380c, 23);
    MD5STEP(F3, a, b, c, d, data[1] + 0xa4beea44, 4);
    MD5STEP(F3, d, a, b, c, data[4] + 0x4bdecfa9, 11);
    MD5STEP(F3, c, d, a, b, data[7] + 0xf6bb4b60, 16);
    MD5STEP(F3, b, c, d, a, data[10] + 0xbebfbc70, 23);
    MD5STEP(F3, a, b, c, d, data[13] + 0x289b7ec6, 4);
    MD5STEP(F3, d, a, b, c, data[0] + 0xeaa127fa, 11);
    MD5STEP(F3, c, d, a, b, data[3] + 0xd4ef3085, 16);
    MD5STEP(F3, b, c, d, a, data[6] + 0x04881d05, 23);
    MD5STEP(F3, a, b, c, d, data[9] + 0xd9d4d039, 4);
    MD5STEP(F3, d, a, b, c, data[12] + 0xe6db99e5, 11);
    MD5STEP(F3, c, d, a, b, data[15] + 0x1fa27cf8, 16);
    MD5STEP(F3, b, c, d, a, data[2] + 0xc4ac5665, 23);

    MD5STEP(F4, a, b, c, d, data[0] + 0xf4292244, 6);
    MD5STEP(F4, d, a, b, c, data[7] + 0x432aff97, 10);
    MD5STEP(F4, c, d, a, b, data[14] + 0xab9423a7, 15);
    MD5STEP(F4, b, c, d, a, data[5] + 0xfc93a039, 21);
    MD5STEP(F4, a, b, c, d, data[12] + 0x655b59c3, 6);
    MD5STEP(F4, d, a, b, c, data[3] + 0x8f0ccc92, 10);
    MD5STEP(F4, c, d, a, b, data[10] + 0xffeff47d, 15);
    MD5STEP(F4, b, c, d, a, data[1] + 0x85845dd1, 21);
    MD5STEP(F4, a, b, c, d, data[8] + 0x6fa87e4f, 6);
    MD5STEP(F4, d, a, b, c, data[15] + 0xfe2ce6e0, 10);
    MD5STEP(F4, c, d, a, b, data[6] + 0xa3014314, 15);
    MD5STEP(F4, b, c, d, a, data[13] + 0x4e0811a1, 21);
    MD5STEP(F4, a, b, c, d, data[4] + 0xf7537e82, 6);
    MD5STEP(F4, d, a, b, c, data[11] + 0xbd3af235, 10);
    MD5STEP(F4, c, d, a, b, data[2] + 0x2ad7d2bb, 15);
    MD5STEP(F4, b, c, d, a, data[9] + 0xeb86d391, 21);

}