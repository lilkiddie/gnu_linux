#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <rhash.h>

#ifdef HAVE_LIBREADLINE
#include <readline/readline.h>
#include <readline/history.h>
#define USE_READLINE 1
#else
#define USE_READLINE 0
#endif

typedef enum {
    HASH_MD5,
    HASH_SHA1,
    HASH_TTH,
    HASH_UNKNOWN
} hash_type_t;

static hash_type_t parse_hash_type(const char *name, int *uppercase) {
    *uppercase = isupper(name[0]);
    
    if (strcasecmp(name, "md5") == 0) {
        return HASH_MD5;
    } else if (strcasecmp(name, "sha1") == 0) {
        return HASH_SHA1;
    } else if (strcasecmp(name, "tth") == 0) {
        return HASH_TTH;
    }
    
    return HASH_UNKNOWN;
}

static unsigned int get_rhash_id(hash_type_t type) {
    switch (type) {
        case HASH_MD5:  return RHASH_MD5;
        case HASH_SHA1: return RHASH_SHA1;
        case HASH_TTH:  return RHASH_TTH;
        default:        return 0;
    }
}

static void print_hash(unsigned char *digest, size_t size, int uppercase) {
    char output[130];
    
    if (uppercase) {
        rhash_print_bytes(output, digest, size, RHPR_HEX | RHPR_UPPERCASE);
    } else {
        rhash_print_bytes(output, digest, size, RHPR_BASE64);
    }
    
    printf("%s\n", output);
}

static int compute_string_hash(const char *str, hash_type_t type, int uppercase) {
    unsigned int hash_id = get_rhash_id(type);
    unsigned char digest[64];
    
    rhash_library_init();
    
    if (rhash_msg(hash_id, str, strlen(str), digest) < 0) {
        fprintf(stderr, "Error: failed to compute hash\n");
        return 1;
    }
    
    size_t digest_size = rhash_get_digest_size(hash_id);
    print_hash(digest, digest_size, uppercase);
    
    return 0;
}

static int compute_file_hash(const char *filename, hash_type_t type, int uppercase) {
    unsigned int hash_id = get_rhash_id(type);
    unsigned char digest[64];
    
    rhash_library_init();
    
    if (rhash_file(hash_id, filename, digest) < 0) {
        fprintf(stderr, "Error: cannot read file '%s'\n", filename);
        return 1;
    }
    
    size_t digest_size = rhash_get_digest_size(hash_id);
    print_hash(digest, digest_size, uppercase);
    
    return 0;
}

static int parse_and_execute(char *input) {
    if (!input || strlen(input) == 0) {
        return 0;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    char *hash_name = strtok(input, " \t");
    char *target = strtok(NULL, " \t");
    
    if (!hash_name || !target) {
        fprintf(stderr, "Error: invalid command format\n");
        return 0;
    }
    
    int uppercase;
    hash_type_t type = parse_hash_type(hash_name, &uppercase);
    
    if (type == HASH_UNKNOWN) {
        fprintf(stderr, "Error: unknown hash algorithm '%s'\n", hash_name);
        return 0;
    }
    
    if (target[0] == '"') {
        compute_string_hash(target + 1, type, uppercase);
    } else {
        compute_file_hash(target, type, uppercase);
    }
    
    return 0;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    int is_interactive = isatty(STDIN_FILENO);
    
    rhash_library_init();
    
    while (1) {
#if USE_READLINE
        if (is_interactive) {
            input = readline("hasher> ");
        } else {
            if (getline(&input, &buffer_size, stdin) == -1) {
                break;
            }
        }
        
        if (!input) {
            break;
        }
        
        if (strlen(input) > 0) {
            if (is_interactive) {
                add_history(input);
            }
            parse_and_execute(input);
        }
        
        free(input);
        input = NULL;
        buffer_size = 0;
#else
        if (is_interactive) {
            printf("hasher> ");
            fflush(stdout);
        }
        
        ssize_t read_len = getline(&input, &buffer_size, stdin);
        if (read_len == -1) {
            break;
        }
        
        parse_and_execute(input);
#endif
    }
    
#if !USE_READLINE
    free(input);
#endif
    
    if (is_interactive) {
        printf("\n");
    }
    
    return 0;
}
