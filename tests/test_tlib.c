#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "test_t_vect.h"

int main(void)
{
    CU_pSuite vect_suite = NULL;

    CU_initialize_registry();
    vect_suite = CU_add_suite("Vect", NULL, NULL);

    test_t_vect_register(vect_suite);

    CU_basic_run_tests();
}
