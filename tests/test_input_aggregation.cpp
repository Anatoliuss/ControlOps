#include "mini_test.hpp"
#include <utils/InputAggregation.hpp>

TEST_CASE(harness_smoke) {
    CHECK(1 + 1 == 2);
}

TEST_CASE(parse_multi_marks_first_primary_rest_alternative) {
    auto v = parseInputOperations("23, 17", "1, 5");
    CHECK(v.size() == 2);
    CHECK(v[0].operation_order == 23);
    CHECK(v[0].deadline == 1);
    CHECK(v[0].is_alternative == false);
    CHECK(v[1].operation_order == 17);
    CHECK(v[1].deadline == 5);
    CHECK(v[1].is_alternative == true);
}

TEST_CASE(parse_single_value) {
    auto v = parseInputOperations("90", "100");
    CHECK(v.size() == 1);
    CHECK(v[0].operation_order == 90);
    CHECK(v[0].deadline == 100);
    CHECK(v[0].is_alternative == false);
}

TEST_CASE(parse_empty_returns_empty) {
    CHECK(parseInputOperations("", "").empty());
}

TEST_CASE(parse_tolerates_whitespace_and_trailing_comma) {
    auto v = parseInputOperations("  4 , 4 ,", " 60 , 260 ");
    CHECK(v.size() == 2);
    CHECK(v[0].operation_order == 4);
    CHECK(v[1].deadline == 260);
}

TEST_CASE(parse_count_mismatch_throws) {
    CHECK_THROWS(parseInputOperations("1, 2, 3", "10, 20"));
}

TEST_CASE(parse_non_integer_throws) {
    CHECK_THROWS(parseInputOperations("1, x", "10, 20"));
}
