#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 4096

#define ERR_ARGS 1
#define ERR_SAME_FILE 2
#define ERR_OPEN_INPUT 10
#define ERR_OPEN_OUTPUT 11
#define ERR_READ 12
#define ERR_WRITE 13
#define ERR_CLOSE_OUTPUT 14
#define ERR_REMOVE 15

int move_file(const char *source_path, const char *dest_path) {
    if (strcmp(source_path, dest_path) == 0) {
        fprintf(stderr, "Error: source and destination are the same\n");
        return ERR_SAME_FILE;
    }

    FILE *input = fopen(source_path, "rb");
    if (!input) {
        fprintf(stderr, "Error: cannot open input file '%s': %s\n", 
                source_path, strerror(errno));
        return ERR_OPEN_INPUT;
    }

    FILE *output = fopen(dest_path, "wb");
    if (!output) {
        fprintf(stderr, "Error: cannot open output file '%s': %s\n", 
                dest_path, strerror(errno));
        fclose(input);
        return ERR_OPEN_OUTPUT;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, output);
        
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Error: write failed: %s\n", strerror(errno));
            fclose(input);
            fclose(output);
            remove(dest_path);
            return ERR_WRITE;
        }
    }

    if (ferror(input)) {
        fprintf(stderr, "Error: read failed: %s\n", strerror(errno));
        fclose(input);
        fclose(output);
        remove(dest_path);
        return ERR_READ;
    }

    fclose(input);

    if (fclose(output) != 0) {
        fprintf(stderr, "Error: cannot close output file: %s\n", strerror(errno));
        return ERR_CLOSE_OUTPUT;
    }

    if (remove(source_path) != 0) {
        fprintf(stderr, "Error: cannot remove source file: %s\n", strerror(errno));
        return ERR_REMOVE;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return ERR_ARGS;
    }

    int result = move_file(argv[1], argv[2]);
    return result;
}
