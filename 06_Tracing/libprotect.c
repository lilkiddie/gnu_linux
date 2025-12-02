#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int remove(const char *path) {
    if (path && strstr(path, "PROTECT")) {
        fprintf(stderr, "Protection: blocked removal of '%s'\n", path);
        errno = EACCES;
        return -1;
    }

    int (*orig_remove)(const char *) = dlsym(RTLD_NEXT, "remove");
    if (!orig_remove) {
        fprintf(stderr, "Error: cannot find original remove()\n");
        return -1;
    }

    return orig_remove(path);
}
