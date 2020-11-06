#define _GNU_SOURCE

#include <string.h>
#include <errno.h>
#include <dlfcn.h>

int unlinkat(int dirfd, const char *filename, int flags) {
    if (strstr(filename, "FIX") != NULL) {
        errno = EPERM;
        return -1;
    }

    return ((int (*) (int, const char*, int)) dlsym(RTLD_NEXT, "unlinkat")) (dirfd, filename, flags);
}
