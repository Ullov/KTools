#ifndef KTOOLS_C_UTILS_H
#define KTOOLS_C_UTILS_H

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

char* KT_utils_get_substr(const char* string, size_t pos, size_t len);

#ifdef __cplusplus
}
#endif

#endif // KTOOLS_C_UTILS_H