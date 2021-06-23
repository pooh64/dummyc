#ifndef __RALLOC_H
#define __RALLOC_H

#include <common.h>
#include <list.h>

typedef struct aregion {
	struct slist_head head;
} aregion_t;

#define RALLOC_BLOCK_SIZE (size_t) (1024 * 64)

static inline void ralloc_init(aregion_t *ar)
{
	slist_head_init(&ar->head);
}

void *ralloc(aregion_t *ar, size_t sz);
void rfree(aregion_t *ar);
void *xmalloc(size_t sz);

#endif