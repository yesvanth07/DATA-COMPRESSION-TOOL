
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to compress using RLE
void compressRLE(FILE *in, FILE *out) {
    char ch, prev;
    int count = 1;

    prev = fgetc(in);
    if (prev == EOF) return;

    while ((ch = fgetc(in)) != EOF) {
        if (ch == prev) {
            count++;
        } else {
            fprintf(out, "%c%d", prev, count);
            prev = ch;
            count = 1;
        }
    }
    fprintf(out, "%c%d", prev, count); // write last set
}

// Function to decompress RLE
void decompressRLE(FILE *in, FILE *out) {
    char ch;
    int count;

    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch) || ch == ' ') {
            fscanf(in, "%d", &count);
            for (int i = 0; i < count; i++)
                fputc(ch, out);
        }
    }
}

int main() {
    // Create input file with hardcoded text
    FILE *f = fopen("input.txt", "w");
    if (f == NULL) {
        printf("Failed to create input file.\n");
        return 1;
    }
    fputs("CODE TECH IT SOLUTIONS", f);
    fclose(f);

    // Open input file for reading
    FILE *in = fopen("input.txt", "r");
    FILE *comp = fopen("compressed.txt", "w");

    if (in == NULL || comp == NULL) {
        printf("File open error.\n");
        return 1;
    }

    compressRLE(in, comp);
    fclose(in);
    fclose(comp);

    // Open compressed file to decompress
    comp = fopen("compressed.txt", "r");
    FILE *decomp = fopen("decompressed.txt", "w");

    if (comp == NULL || decomp == NULL) {
        printf("File open error.\n");
        return 1;
    }

    decompressRLE(comp, decomp);
    fclose(comp);
    fclose(decomp);

    printf("✅ Compression saved to 'compressed.txt'\n");
    printf("✅ Decompression saved to 'decompressed.txt'\n");

    return 0;
}
