#include "aesrand.h"

static void
print_buf(unsigned char *buf, size_t size)
{
    printf("0x");
    for (size_t i = 0; i < size; ++i) {
        printf("%02x", buf[i]);
    }
    printf("\n");
}

int
main(void)
{
    aes_randstate_t rng;
    unsigned char *buf;
    size_t nbits, nbytes;

    if (aes_randinit(rng) == 1)
        return 1;

    nbits = 64;
    buf = random_aes(rng, nbits, &nbytes);
    print_buf(buf, nbytes);
    free(buf);

    nbits = 64;
    buf = random_aes(rng, nbits, &nbytes);
    print_buf(buf, nbytes);
    free(buf);

    {
        mpz_t rop;
        mpz_init(rop);
        if (mpz_urandomb_aes(rop, rng, 128) == AESRAND_ERR)
            return 1;
        gmp_printf("%Zd\n", rop);
    }

    
    return 0;
}
