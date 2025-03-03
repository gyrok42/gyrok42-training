cc_test(
    name = "scheduler",
    srcs = ["scheduler-test.cc"],
    deps = [
        "//src/simple-scheduler:scheduler-lib",
        "@googletest//:gtest_main",  # Updated dependency reference
    ],
    includes = ["include"],  # Include path for headers
    copts = ["-std=c++20", "-Iinclude/simple-scheduler"],
)
