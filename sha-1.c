// SHA-1 Implementation
// no fucking idea if this is correct or not
// clearly doesn't match the outputs from online SHA-1 generators
// so... yeah

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint32_t rotl(uint32_t x, uint32_t bits) {
    return (x << bits) | (x >> (32 - bits));
}

void sha1(uint8_t *message, uint32_t message_len, uint32_t *hash) {
    hash[0] = 0x67452301;
    hash[1] = 0xEFCDAB89;
    hash[2] = 0x98BADCFE;
    hash[3] = 0x10325476;
    hash[4] = 0xC3D2E1F0;

    uint32_t new_len = ((((message_len + 8) / 64) + 1) * 64) - 8;
    uint8_t *msg = calloc(new_len + 64, 1);
    memcpy(msg, message, message_len);
    msg[message_len] = 0x80;
    uint32_t bits_len = message_len * 8;
    memcpy(msg + new_len, &bits_len, sizeof(uint32_t));

    for (uint32_t i = 0; i < new_len; i += 64) {
        uint32_t w[80];
        for (uint32_t j = 0; j < 16; j++) {
            w[j] = (msg[i + j * 4] << 24) |
                   (msg[i + j * 4 + 1] << 16) |
                   (msg[i + j * 4 + 2] << 8) |
                   (msg[i + j * 4 + 3]);
        }
        for (uint32_t j = 16; j < 80; j++) {
            w[j] = rotl((w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]), 1);
        }

        uint32_t a = hash[0], b = hash[1], c = hash[2], d = hash[3], e = hash[4];
        for (uint32_t j = 0; j < 80; j++) {
            uint32_t f, k;
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            uint32_t t = rotl(a, 5) + f + e + k + w[j];
            e = d;
            d = c;
            c = rotl(b, 30);
            b = a;
            a = t;
        }
        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
    }
    free(msg);
}


int main() {
    char *message = "hello world";
    uint32_t len = strlen(message);

    uint32_t hash[5];
    sha1((uint8_t *)message, len, hash);

    printf("SHA-1 hash of '%s': \n", message);
    for (int i = 0; i < 5; i++) {
        printf("%08x ", hash[i]);
    }
    printf("\n");

    return 0;
}
