cc_library(
    name = "circular-queue-lib",
    includes = ["include"],
    hdrs = ["//include/circular-queue:circular-queue.h"],
    srcs = ["circular-queue.cc"],
    visibility = ["//visibility:public", "//tests/circular-queue:__subpackages__"],
    copts = ["-std=c++20", "-Iinclude/circular-queue"],
)

cc_library(
    name = "circular-queue2-lib",
    includes = ["include"],
    hdrs = ["//include/circular-queue:circular-queue2.h"],
    srcs = ["circular-queue2.cc"],
    visibility = ["//visibility:public", "//tests/circular-queue:__subpackages__"],
    copts = ["-std=c++20", "-Iinclude/circular-queue"],
)

cc_library(
    name = "circular-queue3-lib",
    includes = ["include"],
    hdrs = ["//include/circular-queue:circular-queue3.h"],
    srcs = ["circular-queue3.cc"],
    visibility = ["//visibility:public", "//tests/circular-queue:__subpackages__"],
    copts = ["-std=c++20", "-Iinclude/circular-queue"],
)

cc_binary(
    name = "circular-queue-main",
    includes = ["include"],  # Include path for headers
    srcs = ["circular-queue-main.cc"],
    deps = [":circular-queue-lib"],
    copts = ["-std=c++20", "-Iinclude/circular-queue"],
)

cc_binary(
    name = "circular-queue2-main",
    includes = ["include"],  # Include path for headers
    srcs = ["circular-queue2-main.cc"],
    deps = [":circular-queue2-lib"],
    copts = ["-std=c++20", "-Iinclude/circular-queue"],
)

cc_binary(
    name = "circular-queue3-main",
    includes = ["include"],  # Include path for headers
    srcs = ["circular-queue3-main.cc"],
    deps = [":circular-queue3-lib"],
    copts = ["-std=c++20", "-Iinclude/circular-queue"],
)
