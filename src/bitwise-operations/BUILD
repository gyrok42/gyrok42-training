cc_library(
    name = "basic_bit_operations",
    includes = ["include"],  # Include path for headers
    srcs = ["basic_bit_operations.cc"],
    hdrs = ["//include/bitwise-operations:basic_bit_operations.h"],  # Ensure this exists
    visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20"],
)
cc_library(
    name = "flip_bitmap",
    includes = ["include"],  # Include path for headers
    srcs = ["flip_bitmap.cc"],
    hdrs = ["//include/bitwise-operations:flip_bitmap.h", "//include/bitwise-operations:basic_bit_operations.h"],  # Ensure this exists
    visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20"],
)
