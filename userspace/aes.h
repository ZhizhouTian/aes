#ifndef AES_H
#define AES_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef struct {
	uint32_t nr;		// rounds
	uint32_t *rk;		// round_key
	uint32_t buf[68];	// store round_keys, each block is 4 bytes
} aes_context;

#define BLOCK_SIZE 16

#define roundup(x, y) (                                 \
{                                                       \
        typeof(y) __y = y;                              \
        (((x) + (__y - 1)) / __y) * __y;                \
}                                                       \
)

int aes_set_key(aes_context *ctx, const uint8_t *key, uint32_t key_bit);
int aes_encrypt_all(aes_context *ctx, char *output, char *input, int size);
int aes_decrypt_all(aes_context *ctx, char *output, char *input, int size);

#endif
