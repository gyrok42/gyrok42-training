cc_library(
    name = "scheduler-lib",
    hdrs = ["//include/simple-scheduler:scheduler.h", 
    "//include/simple-scheduler:dispatcher.h"],
    srcs = ["scheduler.cc"],
    visibility = ["//tests/simple-scheduler:__subpackages__"],
    copts = ["-std=c++20", "-Iinclude/simple-scheduler"],
)

cc_binary(
    name = "scheduler",
    srcs = ["main.cc"],
    deps = [":scheduler-lib"],
    copts = ["-std=c++20", "-Iinclude/simple-scheduler"],
)
