#ifndef _MSL_C_CTYPE_H
#define _MSL_C_CTYPE_H

#ifdef TARGET_PC
#include_next <ctype.h>
#else

#include "MSL_C/locale.h"
#include "MSL_C/ctype_api.h"

#ifdef __cplusplus
extern "C" {
#endif

__declspec(weak) int isalpha(int __c);
__declspec(weak) int isdigit(int __c);
__declspec(weak) int isspace(int __c);
__declspec(weak) int isupper(int __c);
__declspec(weak) int isxdigit(int __c);

__declspec(weak) int tolower(int __c);
__declspec(weak) int toupper(int __c);

// added underscore to avoid naming conflicts
inline int _isalpha(int c) {
    return (int)(__ctype_map[(unsigned char)c] & __letter);
}
inline int _isdigit(int c) {
    return (int)(__ctype_map[(unsigned char)c] & __digit);
}
inline int _isspace(int c) {
    return (int)(__ctype_map[(unsigned char)c] & __whitespace);
}
inline int _isupper(int c) {
    return (int)(__ctype_map[(unsigned char)c] & __upper_case);
}
inline int _isxdigit(int c) {
    return (int)(__ctype_map[(unsigned char)c] & __hex_digit);
}
inline int _tolower(int c) {
    return (c == -1 ? -1 : (int)__lower_map[(unsigned char)c]);
}
inline int _toupper(int c) {
    return (c == -1 ? -1 : (int)__upper_map[(unsigned char)c]);
}

#ifdef __cplusplus
}
#endif

#endif /* !TARGET_PC */
#endif /* _MSL_C_CTYPE_H */
