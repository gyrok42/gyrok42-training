cc_test(
    name = "vlq",
    srcs = ["vlq-test.cc"],
    deps = [
        "//src/codecs:codecs",
        "@googletest//:gtest_main",  # Updated dependency reference
    ],
    includes = ["include"],  # Include path for headers
    copts = ["-std=c++20", "-Iinclude/codecs"],
)