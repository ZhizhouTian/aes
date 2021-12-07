#include <linux/init.h>
#include <linux/module.h>

#include "aes.h"

void print(const uint8_t *msg, const uint8_t *buf, const uint8_t len)
{
	int i;

	pr_info("%s", msg);
	for(i=0; i< len; ++i)
		pr_info("%02x ", buf[i]);
	pr_info("\n");
}

static int __init aestest_init(void)
{
#define TEXTSIZE (32)
	aes_context ctx;

	uint8_t ret_text[TEXTSIZE] = {0};
	uint8_t cipher_text[TEXTSIZE] = {0};
	uint8_t text[TEXTSIZE] = { 0x0f,0x1e,0x2d,0x3c, 0x4b,0x5a,0x69,0x78, 0x87,0x96,0xa5,0xb4, 0xc3,0xd2,0xe1,0xf0, 0x0f,0x1e,0x2d,0x3c, 0x4b,0x5a,0x69,0x78, 0x87,0x96,0xa5,0xb4, 0xc3,0xd2,0xe1,0xf0 };

	uint8_t key[BLOCK_SIZE] = {0x1f,0x2e,0x21,0x2c, 0x3b,0x52,0x62,0x73, 0x82,0x91,0xb5,0xbc, 0xc5,0xdd,0xe4,0xb0};

	BUG_ON(aes_set_key(&ctx, key, 128));

	BUG_ON(aes_encrypt_all(&ctx, cipher_text, text, TEXTSIZE));

	BUG_ON(aes_decrypt_all(&ctx, ret_text, cipher_text, TEXTSIZE));

	print("\tkey    :  ", key , BLOCK_SIZE);
	print("\tinput  :  ", text, TEXTSIZE);
	print("\tencrypt:  ", cipher_text, TEXTSIZE);
	print("\tdecrypt:  ", ret_text, TEXTSIZE);

	return 0;
}

static void __exit aestest_exit(void)
{
}

module_init(aestest_init);
module_exit(aestest_exit);
MODULE_LICENSE("Tencent");
