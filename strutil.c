/*
 * Copyright (c) 1997-2015 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <errno.h>
#include <string.h>

#define STRUTIL_PATH_MAX 4096

size_t strutil_strlcpy(char *dst, const char *src, size_t dsize) {
    const char *osrc = src;
    size_t nleft = dsize;

    /* Copy as many bytes as will fit. */
    if (nleft != 0) {
        while (--nleft != 0) {
            if ((*dst++ = *src++) == '\0') {
                break;
            }
        }
    }

    /* Not enough room in dst, add NUL and traverse rest of src. */
    if (nleft == 0) {
        if (dsize != 0) {
            *dst = '\0'; /* NUL-terminate dst */
        }
        while (*src++) {
            /* Do nothing */
        }
    }

    return src - osrc - 1; /* count does not include NUL */
}

size_t strutil_strlcat(char *dst, const char *src, size_t dsize) {
    const char *odst = dst;
    const char *osrc = src;
    size_t n = dsize;
    size_t dlen;

    /* Find the end of dst and adjust bytes left but don't go past end. */
    while (n-- != 0 && *dst != '\0') {
        dst++;
    }

    dlen = dst - odst;
    n = dsize - dlen;

    if (n-- == 0) {
        return dlen + strlen(src);
    }

    while (*src != '\0') {
        if (n != 0) {
            *dst++ = *src;
            n--;
        }
        src++;
    }

    *dst = '\0';

    return dlen + (src - osrc); /* count does not include NUL */
}


char *strutil_basename(const char *path) {
    static char bname[STRUTIL_PATH_MAX];
    size_t len;
    const char *endp, *startp;

    /* Empty or NULL string gets treated as "." */
    if (path == NULL || *path == '\0') {
        bname[0] = '.';
        bname[1] = '\0';
        return bname;
    }

    /* Strip any trailing slashes */
    endp = path + strlen(path) - 1;
    while (endp > path && *endp == '/') {
        endp--;
    }

    /* All slashes becomes "/" */
    if (endp == path && *endp == '/') {
        bname[0] = '/';
        bname[1] = '\0';
        return bname;
    }

    /* Find the start of the base */
    startp = endp;
    while (startp > path && *(startp - 1) != '/') {
        startp--;
    }

    len = endp - startp + 1;
    if (len >= sizeof(bname)) {
        errno = ENAMETOOLONG;
        return NULL;
    }

    memcpy(bname, startp, len);
    bname[len] = '\0';

    return bname;
}
