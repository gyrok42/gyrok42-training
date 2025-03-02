cc_library(
    name = "scheduler_ii_lib",
    hdrs = ["//include/simple-scheduler:scheduler.h"],
    srcs = ["scheduler.cc"],
    visibility = ["//visibility:public"],
    copts = ["-std=c++20", "-Iinclude/simple-scheduler"],
)

cc_binary(
    name = "scheduler",
    srcs = ["main.cc"],
    deps = [":scheduler_ii_lib"],
    copts = ["-std=c++20", "-Iinclude/simple-scheduler"],
)
