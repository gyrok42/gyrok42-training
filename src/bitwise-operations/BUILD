cc_library(
    name = "basic_bit_operations",
    includes = ["include"],  # Include path for headers
    srcs = ["basic_bit_operations.cc"],
    hdrs = ["//include/bitwise-operations:basic_bit_operations.h"],  # Ensure this exists
    visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
)
cc_library(
    name = "reverse_rows",
    includes = ["include"],  # Include path for headers
    srcs = ["reverse_rows.cc"],
    hdrs = ["//include/bitwise-operations:reverse_rows.h", "//include/bitwise-operations:basic_bit_operations.h"],  # Ensure this exists
    visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
)
