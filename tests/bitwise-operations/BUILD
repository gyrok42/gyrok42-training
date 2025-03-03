cc_test(
    name = "basic-bit-operations-test",
    srcs = ["basic-bit-operations-test.cc"],
    deps = [
        "//src/bitwise-operations:basic-bit-operations",
        "@googletest//:gtest_main",  # Updated dependency reference
    ],
    includes = ["include"],  # Include path for headers
    copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
)

cc_test(
    name = "reverse-rows-test",
    srcs = ["reverse-rows-test.cc"],
    deps = [
        "//src/bitwise-operations:basic-bit-operations",
        "//src/bitwise-operations:reverse-rows",
        "@googletest//:gtest_main",  # Updated dependency reference
    ],
    includes = ["include"],  # Include path for headers
    copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
)

cc_test(
    name = "bit-manipulation-tricks-test",
    srcs = ["bit-manipulation-tricks-test.cc"],
    deps = [
        "//src/bitwise-operations:bit-manipulation-tricks",
        "@googletest//:gtest_main",  # Updated dependency reference
    ],
    includes = ["include"],  # Include path for headers
    copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
)
