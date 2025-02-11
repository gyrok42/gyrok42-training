cc_test(
    name = "basic_bit_operations_test",
    srcs = ["basic_bit_operations_test.cc"],
    deps = [
        "//src/bitwise-operations:basic_bit_operations",
        "@googletest//:gtest_main",  # Updated dependency reference
    ],
    includes = ["include"],  # Include path for headers
)

cc_test(
    name = "flip_bitmap_test",
    srcs = ["flip_bitmap_test.cc"],
    deps = [
        "//src/bitwise-operations:basic_bit_operations",
        "//src/bitwise-operations:flip_bitmap",
        "@googletest//:gtest_main",  # Updated dependency reference
    ],
    includes = ["include"],  # Include path for headers
)
