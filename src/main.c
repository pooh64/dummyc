#include "common.h"
#include "logger.h"
#include "ralloc.h"
#include "strtab.h"
#include <string.h>
#include <stdlib.h>

void test_ralloc()
{
	void *mem_arr[20];
	u8 *ptr;
	aregion_t ar;
	size_t mem_sz;
	ralloc_init(&ar);

	logger("RALLOC_TEST");

	for (size_t i = 0; i < ARRAY_SIZE(mem_arr); ++i) {
		mem_sz = (size_t)1 << i;
		mem_sz += mem_sz / 4;
		mem_arr[i] = ralloc(&ar, mem_sz);
		memset(mem_arr[i], i, mem_sz);
	}

	for (size_t i = 0; i < ARRAY_SIZE(mem_arr); ++i) {
		mem_sz = (size_t)1 << i;
		mem_sz += mem_sz / 4;
		ptr = mem_arr[i];
		while (mem_sz--) {
			if (*ptr != i)
				logger_fatal("memory rewritten!");
			ptr++;
		}
	}
	rfree(&ar);
	logger("OK");
}

void test_strht()
{
	char buf[32] = { 0 };
	char const *str, *ptrhello;

	logger("STRHT_TEST");

	ptrhello = strtab_string("hello plumcc!");

	for (u32 i = 0; i < 4096 * 32; ++i) {
		for (u32 j = 0; j < ARRAY_SIZE(buf) - 1; j++)
			buf[j] = rand();
		str = strtab_string(buf);
		if (strcmp(str, buf))
			logger_fatal("strings differ!");
	}

	if (ptrhello != strtab_string("hello plumcc!"))
		logger_fatal("pointers differ!");

	strtab_stringd(INT32_MIN);
	strtab_clean();
	logger("OK");
}

int main()
{
	logger("starting main");
	test_ralloc();
	test_strht();
	logger_fatal("quack!");

	return 0;
}