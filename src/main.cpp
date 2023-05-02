#include <string>
#include <cstdio>
#include <cstring>
// #include "arc4.h"
#include "rc4.cpp"

#define BUF_SIZE 4096
#define SALT_SIZE 8

int main(int argc, char *argv[]) {
    // ARC4 rc4;
    RC4 rc4;
    if (argc != 5 && argc != 6) {
        printf("incorrect usage: rc4 <encrypt|decrypt> <input> <output> <key> [salt]\n");
        return 1;
    }

    // Load input and output files
    FILE *in = fopen(argv[2], "rb");
    if (!in) {
        printf("failed to open input file %s\n", argv[2]);
        return 1;
    }
    FILE *out = fopen(argv[3], "wb");
    if (!out) {
        printf("failed to open output file %s\n", argv[3]);
        fclose(in);
        return 1;
    }

    // Handle the salt if present
    if(argc == 6) {
        char *salt = argv[5];
        if(strcmp(argv[1], "encrypt") == 0) {
            rc4.set_key((unsigned char *) argv[4], (int) ((std::string) argv[4]).size());
            rc4.encrypt(salt, salt, sizeof(salt)/sizeof(salt[0]));
            fwrite("Salted__", 1, 8, out);
            fwrite(salt, 1, SALT_SIZE, out);
        } else {
            fseek(in, 16, SEEK_SET);
        }
    }

    // Encrypt or decrypt the input data
    unsigned char bufIn[BUF_SIZE], bufOut[BUF_SIZE];
    int read, written;
    while ((read = fread(bufIn, 1, BUF_SIZE, in)) > 0)
    {
        rc4.set_key((unsigned char *) argv[4], (int) ((std::string) argv[4]).size());
        rc4.encrypt(bufIn, bufOut, sizeof(bufIn)/sizeof(bufIn[1]));
        written = fwrite(bufOut, 1, read, out);
        if (written != read)
        {
            printf("failed to write to output file %s\n", argv[3]);
            fclose(in);
            fclose(out);
            return 1;
        }
    }
    fclose(in);
    fclose(out);
}
