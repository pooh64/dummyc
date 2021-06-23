#include <common.h>
#include <logger.h>
#include <ralloc.h>
#include <string.h>

void test_ralloc()
{
	void *mem_arr[20];
	u8 *ptr;
	aregion_t ar;
	size_t mem_sz;
	ralloc_init(&ar);

	logger("RALLOC_TEST");

	for (size_t i = 0; i < ARRAY_SIZE(mem_arr); ++i) {
		mem_sz = (size_t) 1 << i;
		mem_sz += mem_sz / 4;
		mem_arr[i] = ralloc(&ar, mem_sz);
		memset(mem_arr[i], i, mem_sz);
	}

	for (size_t i = 0; i < ARRAY_SIZE(mem_arr); ++i) {
		mem_sz = (size_t) 1 << i;
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

int main()
{
	logger("starting main");
	test_ralloc();
	logger_fatal("quack!");

	return 0;
}