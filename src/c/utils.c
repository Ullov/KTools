#include "./utils.h"

#include <string.h>
#include <stdlib.h>

char* KT_utils_get_substr(const char* string, size_t pos, size_t len)
{
    char* res = malloc(sizeof(char) * (len + 1));
    memcpy(res, &string[pos], len);
    res[len] = 0;
    return res;
}