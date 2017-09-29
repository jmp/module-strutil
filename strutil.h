#ifndef STRUTIL_H
#define STRUTIL_H

#include <stddef.h>

/*
 * Copy string src to buffer dst of size dsize.  At most dsize-1
 * chars will be copied.  Always NUL terminates (unless dsize == 0).
 * Returns strlen(src); if retval >= dsize, truncation occurred.
 */
extern size_t strutil_strlcpy(char *dst, const char *src, size_t dsize);

/*
 * Appends src to string dst of size dsize (unlike strncat, dsize is the
 * full size of dst, not space left).  At most dsize-1 characters
 * will be copied.  Always NUL terminates (unless dsize <= strlen(dst)).
 * Returns strlen(src) + MIN(dsize, strlen(initial dst)).
 * If retval >= dsize, truncation occurred.
 */
extern size_t strutil_strlcat(char *dst, const char *src, size_t dsize);

/*
 * Basename
 */
extern char *strutil_basename(const char *path);

#endif /* STRUTIL_H */
