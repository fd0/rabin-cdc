#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include "rabin.h"

// 1MiB buffer
uint8_t buf[1024*1024];
size_t bytes;

int main(void) {
    struct rabin_t *hash;
    hash = rabin_init();

    unsigned int chunks = 0;

    while (!feof(stdin)) {
        size_t len = fread(buf, 1, sizeof(buf), stdin);
        uint8_t *ptr = &buf[0];

        // printf("read %zd bytes\n", len);

        bytes += len;

        while (1) {
            // printf("  rabin_next_chunk(%p, %zd)\n", ptr, len);
            int remaining = rabin_next_chunk(hash, ptr, len);

            // printf("  rabin remaining: %d bytes, len %zd\n", remaining, len);

            if (remaining < 0) {
                break;
            }

            len -= remaining;
            ptr += remaining;

            // printf("remaining: %d, len %zd, ptr %p\n", remaining, len, ptr);

            printf("%d %016llx\n",
                last_chunk.length,
                (long long unsigned int)last_chunk.cut_fingerprint);

            chunks++;

            // printf("  next bytes: %02x%02x%02x%02x\n", *ptr, *(ptr+1), *(ptr+2), *(ptr+3));
        }
    }

    rabin_finalize(hash);
    chunks++;

    printf("%d %016llx\n",
        last_chunk.length,
        (long long unsigned int)last_chunk.cut_fingerprint);

    unsigned int avg = 0;
    if (chunks > 0)
        avg = bytes / chunks;
    printf("%d chunks, average chunk size %d\n", chunks, avg);

    return 0;
}
