#ifndef T_VECT_H
#define T_VECT_H
#include "t_global.h"
#include <stddef.h>

#define TV_DEFAULT_SIZE 16

typedef enum t_vect_err
{
    TV_ERR_OK = 0,
    TV_ERR_NOMEM = -1,
    TV_ERR_NOELM = -2,
} t_vect_err;

struct t_vect
{
    size_t size;
    size_t taken;
    // For when the vect is freed
    freefunc free;

    void **items;
};

struct t_vect *t_vect_new(freefunc free);
t_vect_err t_vect_ensure(struct t_vect *self, size_t capacity);

t_vect_err t_vect_add(struct t_vect *self, void *item);
t_vect_err t_vect_del(struct t_vect *self, size_t offset);
t_vect_err t_vect_delfree(struct t_vect *self, size_t offset);

t_vect_err t_vect_get(struct t_vect *self, size_t offset, void **out);
t_vect_err t_vect_set(struct t_vect *self, size_t offset, void *item);
t_vect_err t_vect_setfree(struct t_vect *self, size_t offset, void *item);

void t_vect_free(struct t_vect **s);

const char *t_vect_errstr(t_vect_err err);
#endif
