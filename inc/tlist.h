#ifndef T_LIST_H
#define T_LIST_H
struct t_list {
    struct t_list *last;
    void *cur;
    struct t_list *next;
};

tlist tlist_new(void *first, ...);
void tlist_enque(tlist *list, void *item);
void tlist_push(tlist *first, void *item);

void *tlist_pop(tlist *list);
void *tlist_dequeue(tlist *list);

#endif
