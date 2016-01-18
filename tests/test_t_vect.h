#ifndef TEST_T_VECT
#define TEST_T_VECT
#include <stdbool.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>

#include "t_vect.h"

void test_t_vect_new()
{
    struct t_vect *tmp = t_vect_new(free);
    CU_ASSERT(tmp != NULL);
    CU_ASSERT((tmp->size == tmp->taken == 0));
    CU_ASSERT(tmp->items != NULL);
    CU_PASS("Testing that the size is right. Test fails if it crashes");
    void *tst = tmp->items[TV_DEFAULT_SIZE - 1];
    CU_PASS("Size test passed");
    CU_ASSERT(tmp->free == free);
}

void test_t_vect_ensure()
{
    const size_t sixteenmeg = 16777216;
    struct t_vect *tmp = t_vect_new(NULL);
    t_vect_ensure(tmp, 16777216);
    CU_ASSERT(tmp->size = sixteenmeg);
    CU_ASSERT(tmp->taken == 0);
}

void test_t_vect_add(void)
{
    struct t_vect *tmp = t_vect_new(NULL);

    for (int i = 0; i < 64; i++)
    {
        t_vect_add(tmp, (void*)i);
    }

    CU_ASSERT(tmp->size == 64);
    CU_ASSERT(tmp->taken == 64);

    bool brokenEntry = false;
    for (int i = 0; i < 64; i++)
    {
        if ((int)tmp->items[i] != i)
        {
            brokenEntry = true;
            break;
        }
    }

    CU_ASSERT_FALSE(brokenEntry);
}

void test_t_vect_del()
{
    struct t_vect *tmp = t_vect_new(NULL);

    for (int i = 0; i < 64; i++)
    {
        t_vect_add(tmp, (void*)i);
    }

    t_vect_del(tmp, 0);
    CU_ASSERT(tmp->items[0] == 1);
    CU_ASSERT(tmp->taken == 63);
    CU_ASSERT(t_vect_del(tmp, 128) == TV_ERR_NOELM);
    CU_ASSERT(t_vect_del(tmp, 63) == TV_ERR_NOELM);
    t_vect_del(tmp, 32);
    CU_ASSERT(tmp->items[32] == 34);
}

void test_t_vect_delfree()
{
    struct t_vect *tmp = t_vect_new(free);

    
    for (int i = 0; i < 64; i++)
    {
        int *t = malloc(sizeof(int));
        *t = i;
        t_vect_add(tmp, t);
    }

    t_vect_delfree(tmp, 0);
    CU_ASSERT(tmp->taken == 63);
    CU_ASSERT(*(int*)tmp->items[0] == 1);
    CU_ASSERT(tmp->taken == 63);
    CU_ASSERT(t_vect_delfree(tmp, 128) == TV_ERR_NOELM);
    CU_ASSERT(t_vect_delfree(tmp, 63) == TV_ERR_NOELM);
    t_vect_delfree(tmp, 32);
    CU_ASSERT(*(int*)tmp->items[32] == 34);
}

void test_t_vect_get(void)
{
    struct t_vect *tmp = t_vect_new(NULL);

    for (int i = 0; i < 64; i++)
    {
        t_vect_add(tmp, (void*)i);
    }

    CU_ASSERT(tmp->size == 64);
    CU_ASSERT(tmp->taken == 64);
    CU_ASSERT(t_vect_get(tmp, 128, NULL) == TV_ERR_NOELM);
    
    bool brokenEntry = false;
    for (int i = 0; i < 64; i++)
    {
        int *val;
        t_vect_get(tmp, i, &val);
        if (val != i ||
            val != tmp->items[i])
        {
            brokenEntry = true;
            break;
        }
    }

    CU_ASSERT_FALSE(brokenEntry);
}

void test_t_vect_set(void)
{
    struct t_vect *tmp = t_vect_new(NULL);

    for (int i = 0; i < 64; i++)
    {
        t_vect_add(tmp, (void*)i);
    }

    t_vect_set(tmp, 4, 0xff);
    CU_ASSERT(tmp->size == 64);
    CU_ASSERT(tmp->taken == 64);
    CU_ASSERT(t_vect_set(tmp, 128, NULL) == TV_ERR_NOELM);    
    int val;
    t_vect_get(tmp, 4, &val);
    CU_ASSERT(val == 0xff);
    

}

void test_t_vect_setfree()
{
    struct t_vect *tmp = t_vect_new(free);

    
    for (int i = 0; i < 64; i++)
    {
        int *t = malloc(sizeof(int));
        *t = i;
        t_vect_add(tmp, t);
    }

    t_vect_setfree(tmp, 4, 0xff);
    CU_ASSERT(tmp->size == 64);
    CU_ASSERT(tmp->taken == 64);
    CU_ASSERT(t_vect_set(tmp, 128, NULL) == TV_ERR_NOELM);    
    int val;
    t_vect_get(tmp, 4, &val);
    CU_ASSERT(val == 0xff);
}
void test_t_vect_free()
{
    struct t_vect *tmp = t_vect_new(free);

    
    for (int i = 0; i < 64; i++)
    {
        int *t = malloc(sizeof(int));
        *t = i;
        t_vect_add(tmp, t);
    }

    t_vect_free(&tmp);
    CU_ASSERT(tmp == NULL);
}

void test_t_vect_register(CU_pSuite suite)
{
    CU_add_test(suite, "Test of t_vect_new", test_t_vect_new);
        CU_add_test(suite, "Test of t_vect_free", test_t_vect_free);
    CU_add_test(suite, "Test of t_vect_ensure", test_t_vect_ensure);
    CU_add_test(suite, "Test of t_vect_add", test_t_vect_add);
    CU_add_test(suite, "Test of t_vect_del", test_t_vect_del);
    CU_add_test(suite, "Test of t_vect_get", test_t_vect_get);
    CU_add_test(suite, "Test of t_vect_set", test_t_vect_set);
    CU_add_test(suite, "Test of t_vect_delfree", test_t_vect_delfree);
    


}
#endif
