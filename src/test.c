#include <check.h>
#include <ncurses.h>
#include <stdio.h>
#include <backend.h>

Suite *test_suite();

Suite *test_suite(void) {
    Suite *s = suite_create("tetris_backend");

    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_random_range);

    suite_add_tcase(s, tc);

    return s;
}

START_TEST(test_random_range)
{
    int max = 7;
    int num = GenerateRandomNum(max);

    ck_assert_int_ge(num, 0);
    ck_assert_int_lt(num, max);
}
END_TEST


int main(void)
{
    int number_failed;
    Suite *s = test_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}