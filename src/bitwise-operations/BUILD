cc_library(
    name = "flip_bitmap",
    includes = ["include"],  # Include path for headers
    srcs = ["flip_bitmap.cc"],
    hdrs = ["//include/bitwise-operations:flip_bitmap.h"],  # Ensure this exists
    visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20"],
)
