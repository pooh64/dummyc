#ifndef __STRHT_H
#define __STRHT_H

#include "common.h"

char const *strtab_string(char const *str);
char const *strtab_stringn(char const *str, u16 len);
char const *strtab_stringd(i32 i);
void strtab_clean();

#endif