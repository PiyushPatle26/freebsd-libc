/*
 * Memory allocation stubs - redirect to Unikraft's allocator
 * This provides FreeBSD libc memory functions using Unikraft's uk_malloc
 */

#include <uk/alloc.h>
#include <uk/essentials.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

/* Default allocator instance */
extern struct uk_alloc *uk_alloc_get_default(void);

void *malloc(size_t size)
{
    return uk_malloc(uk_alloc_get_default(), size);
}

void free(void *ptr)
{
    uk_free(uk_alloc_get_default(), ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    return uk_calloc(uk_alloc_get_default(), nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
    return uk_realloc(uk_alloc_get_default(), ptr, size);
}

char *strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup != NULL) {
        memcpy(dup, s, len);
    }
    return dup;
}

char *strndup(const char *s, size_t n)
{
    size_t len = strnlen(s, n);
    char *dup = malloc(len + 1);
    if (dup != NULL) {
        memcpy(dup, s, len);
        dup[len] = '\0';
    }
    return dup;
}

int asprintf(char **strp, const char *fmt, ...)
{
    /* Simple stub - not implementing full asprintf for now */
    *strp = NULL;
    errno = ENOSYS;
    return -1;
}