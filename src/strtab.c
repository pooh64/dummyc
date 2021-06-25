#include "list.h"
#include "logger.h"
#include "ralloc.h"
#include "strtab.h"
#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#define STRTAB_BITS 12

struct strtab {
	DECLARE_HTABLE(ht, STRTAB_BITS);
	aregion_t ar;
} g_strtab = { .ht = { SLIST_HEAD_INIT }, .ar = RALLOC_INIT };

struct strtab_entry {
	struct slist_head list;
	u16 len;
	char str[];
};

static inline u32 djb2_hash(char const *s, u16 len)
{
	u32 h = 5381;
	for (u8 c = *s; len; c = *++s, --len)
		h = h * 33 + c;
	return h;
}

char const *strtab_stringn(char const *str, u16 len)
{
	struct strtab_entry *entry;
	u32 hash = djb2_hash(str, len);

	htable_for_each_possible(g_strtab.ht, entry, list, hash)
	{
		if (entry->len != len)
			continue;
		if (memcmp(str, entry->str, len))
			continue;
		return entry->str;
	}

	entry = ralloc(&g_strtab.ar, sizeof(*entry) + len + 1);
	entry->len = len;
	memcpy(entry->str, str, len);
	entry->str[len] = 0;
	htable_add(g_strtab.ht, hash, &entry->list);
	return entry->str;
}

char const *strtab_string(char const *str)
{
	size_t len = strlen(str);
	if (len > UINT16_MAX)
		logger_fatal("input string is too long");
	return strtab_stringn(str, len);
}

char const *strtab_stringd(i32 i)
{
	char str[12];
	u16 len = sprintf(str, "%" PRIi32, i);
	return strtab_stringn(str, len);
}

void strtab_clean()
{
	memset(g_strtab.ht, 0, sizeof(g_strtab.ht));
	rfree(&g_strtab.ar);
}