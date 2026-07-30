#include "string.h" /* strchr */

#include "libultra/xprintf.h"

#define isdigit(x) ((x >= '0' && x <= '9'))
#define LDSIGN(x) (((unsigned short *)&(x))[0] & 0x8000)

#define ATOI(dst, src)                   \
    for (dst = 0; isdigit(*src); ++src)  \
    {                                    \
        if (dst < 999)                   \
            dst = dst * 10 + *src - '0'; \
    }

#define MAX_PAD ((33 - 1))
#define PAD(s, n)                                             \
    if (0 < (n))                                              \
    {                                                         \
        int i, j = (n);                                       \
        for (; 0 < j; j -= i)                                 \
        {                                                     \
            i = MAX_PAD < j ? (int)MAX_PAD : j; \
            PUT(s, i);                                        \
        }                                                     \
    }
#define PUT(s, n)                                \
    if (0 < (n))                                 \
    {                                            \
        if ((arg = (*pfn)(arg, s, n)) != NULL) \
            x.nchar += (n);                      \
        else                                     \
            return x.nchar;                      \
    }

static char spaces[] = "                                ";
static char zeroes[] = "00000000000000000000000000000000";

void _Putfld(_Pft*, va_list, u8, u8*);

int _Printf(void* (*pfn)(void*, const char*, int), void* arg, const char* fmt, va_list args) {
    _Pft x;
    
    x.nchar = 0;

    while (TRUE) {
        const char *s;
        char c;
        const char *t;
        static const char fchar[] = {' ', '+', '-', '#', '0', '\0'};
        static const int fbit[] = {FLAGS_SPACE, FLAGS_PLUS, FLAGS_MINUS, FLAGS_HASH, FLAGS_ZERO, 0};
        char ac[32];
        s = fmt;

        for (c = *s; c != 0 && c != '%';) {
            c = *++s;
        }
        
        PUT(fmt, (u32)(s - fmt));
        
        if (c == 0) {
            return x.nchar;
        }
        
        fmt = ++s;
        
        for (x.flags = 0; (t = strchr(fchar, *s)) != NULL; s++) {
            x.flags |= fbit[t - fchar];
        }

        if (*s == '*') {
            x.width = va_arg(args, int);

            if (x.width < 0) {
                x.width = -x.width;
                x.flags |= FLAGS_MINUS;
            }
            s++;
        } else 
            ATOI(x.width, s);


        if (*s != '.') {
            x.prec = -1;
        } else if (*++s == '*') {
            x.prec = va_arg(args, int);
            ++s;
        } else
            ATOI(x.prec, s);


        x.qual = strchr("hlL", *s) ? *s++ : '\0';
        
        if (x.qual == 'l' && *s == 'l') {
            x.qual = 'L';
            ++s;
        }

        _Putfld(&x, args, *s, (u8*)ac);
        x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;

       {

            if (!(x.flags & FLAGS_MINUS)) {
                int i, j;
                if (0 < (x.width))
                {
                    i, j = x.width;
                    for (; 0 < j; j -= i)
                    {
                        i = MAX_PAD < j ? (int)MAX_PAD : j;
                        PUT(spaces, i);
                    }
                }
            }

            PUT(ac, x.n0);
            PAD(zeroes, x.nz0)

            PUT(x.s, x.n1);
            PAD(zeroes, x.nz1);

            PUT(x.s + x.n1, x.n2);
            PAD(zeroes, x.nz2);

            if (x.flags & FLAGS_MINUS) {
                PAD(spaces, x.width);
            }
        }
        fmt = s + 1;
    }
    return 0;
}

void _Putfld(_Pft* px, va_list ap, u8 code, u8* ac) {
    px->n0 = px->nz0 = px->n1 = px->nz1 = px->n2 = px->nz2 = 0;

    switch ((u8)code) {
        case 'c':
            ac[px->n0++] = va_arg(ap, u32);
            break;

        case 'd':
        case 'i':
            if (px->qual == 'l') {
                px->v.ll = va_arg(ap, s32);
            } else if (px->qual == 'L') {
                px->v.ll = va_arg(ap, s64);
            } else {
                px->v.ll = va_arg(ap, s32);
            }

            if (px->qual == 'h') {
                px->v.ll = (s16)px->v.ll;
            }

            if (px->v.ll < 0) {
                ac[px->n0++] = '-';
            } else if (px->flags & FLAGS_PLUS) {
                ac[px->n0++] = '+';
            } else if (px->flags & FLAGS_SPACE) {
                ac[px->n0++] = ' ';
            }

            px->s = (char*)&ac[px->n0];

            _Litob(px, code);
            break;
        case 'x':
        case 'X':
        case 'u':
        case 'o':
            if (px->qual == 'l') {
                px->v.ll = va_arg(ap, s32);
            } else if (px->qual == 'L') {
                px->v.ll = va_arg(ap, s64);
            } else {
                px->v.ll = va_arg(ap, s32);
            }

            if (px->qual == 'h') {
                px->v.ll = (u16)px->v.ll;
            } else if (px->qual == 0) {
                px->v.ll = (u32)px->v.ll;
            }

            if (px->flags & FLAGS_HASH) {
                ac[px->n0++] = '0';
                if (code == 'x' || code == 'X') {

                    ac[px->n0++] = code;
                }
            }
            px->s = (char*)&ac[px->n0];
            _Litob(px, code);
            break;
        case 'e':
        case 'f':
        case 'g':
        case 'E':
        case 'G':
            px->v.ld = px->qual == 'L' ? va_arg(ap, f64) : va_arg(ap, f64);

            if (*(u16*)&px->v.ll & 0x8000) {
                ac[px->n0++] = '-';
            } else {
                if (px->flags & FLAGS_PLUS) {
                    ac[px->n0++] = '+';
                } else if (px->flags & FLAGS_SPACE) {
                    ac[px->n0++] = ' ';
                }
            }

            px->s = (char*)&ac[px->n0];
            _Ldtob(px, code);
            break;
        case 'n':
            if (px->qual == 'h') {
                *(va_arg(ap, s16*)) = px->nchar;
            } else if (px->qual == 'l') {
                *va_arg(ap, s32*) = px->nchar;
            } else if (px->qual == 'L') {
                *va_arg(ap, s64*) = px->nchar;
            } else {
                *va_arg(ap, s32*) = px->nchar;
            }
            break;

        case 'p':
#ifdef TARGET_PC
            px->v.ll = (u64)(uintptr_t)va_arg(ap, void*);
#else
            px->v.ll = (s32)va_arg(ap, void*);
#endif
            px->s = (char*)&ac[px->n0];
            _Litob(px, 'x');
            break;
        case 's':
            px->s = va_arg(ap, char*);
            px->n1 = strlen(px->s);
            if (px->prec >= 0 && px->prec < px->n1) {
                px->n1 = px->prec;
            }
            break;
        case '%':
            ac[px->n0++] = '%';
            break;
        default:
            ac[px->n0++] = code;
            break;
    }
}
