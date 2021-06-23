#ifndef __LIST_H
#define __LIST_H

#include <common.h>

struct slist_head {
	struct slist_head *next;
};

static inline void slist_head_init(struct slist_head *h)
{
	h->next = NULL;
}

static inline void slist_add_head(struct slist_head *h, struct slist_head *n)
{
	n->next = h->next;
	h->next = n;
}

static inline int slist_empty(struct slist_head *h)
{
	return !(h->next);
}

static inline struct slist_head *slist_peek_head(struct slist_head *h)
{
	return h->next;
}

static inline struct slist_head *slist_pop_head(struct slist_head *h)
{
	struct slist_head *n = h->next;
	if (n) {
		h->next = n->next;
		n->next = NULL;
	}
	return n;
}

#define slist_for_each(h, p) for (p = (h)->next; p; p = p->next)

#define slist_entry_safe(ptr, type, member)                                    \
	({                                                                     \
		typeof(ptr) __ptr = (ptr);                                     \
		__ptr ? container_of(__ptr, type, member) : NULL;              \
	})

#define slist_for_each_entry(h, p, m)                                          \
	for (p = slist_entry_safe((h)->next, typeof(*(p)), m); p;              \
	     p = slist_entry_safe((p)->m.next, typeof(*(p)), m))

#define DECLARE_HTABLE(name, bits) struct slist_head name[1 << (bits)]
#define htable_add(ht, hv, n) slist_add_head(&ht[min((size_t) hv, ARRAY_SIZE(ht)], n)

#endif