#include "ralloc.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>

struct ablock {
	struct slist_head list;
	void *end;
	void *cur;
};

union __ralloc_align {
	size_t s;
	double d;
	void *p;
	void (*fp)(void);
};

#define RALLOC_ALIGN sizeof(union __ralloc_align)

void *xmalloc(size_t sz)
{
	void *p = malloc(sz);
	if (!p)
		logger_fatal("fatal: out of memory");
	return p;
}

void *ralloc(aregion_t *ar, size_t sz)
{
	struct ablock *ab;
	size_t blk_sz;

	sz = roundup(sz, RALLOC_ALIGN);

	if (slist_empty(&ar->head))
		goto alloc_new;

	ab = container_of(slist_peek_head(&ar->head), typeof(*ab), list);
	if (sz <= ab->end - ab->cur)
		goto alloc_out;

alloc_new:
	blk_sz = max(RALLOC_BLOCK_SIZE, sz);
	blk_sz += roundup(sizeof(struct ablock), RALLOC_ALIGN);
	blk_sz = next_pow2_64(blk_sz);
	ab = xmalloc(blk_sz);
	ab->cur = (u8*) ab + roundup(sizeof(struct ablock), RALLOC_ALIGN);
	ab->end = (u8*) ab + blk_sz;
	slist_head_init(&ab->list);
	slist_add_head(&ar->head, &ab->list);
alloc_out:
	ab->cur += sz;
	return ab->cur - sz;
}

void *rcalloc(aregion_t *ar, size_t sz)
{
	return memset(ralloc(ar, sz), 0, sz);
}

void rfree(aregion_t *ar)
{
	logger("aregion %p freed", ar);
	struct ablock *ab;
	while (!slist_empty(&ar->head)) {
		ab = container_of(slist_pop_head(&ar->head), typeof(*ab), list);
		free(ab);
	}
}