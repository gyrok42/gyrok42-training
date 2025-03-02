cc_library(
    name = "basic-bit-operations",
    includes = ["include"],  # Include path for headers
    srcs = ["basic-bit-operations.cc"],
    hdrs = ["//include/bitwise-operations:basic-bit-operations.h"],  # Ensure this exists
    visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
)
cc_library(
    name = "reverse-rows",
    includes = ["include"],  # Include path for headers
    srcs = ["reverse-rows.cc"],
    hdrs = ["//include/bitwise-operations:reverse-rows.h", 
    "//include/bitwise-operations:basic-bit-operations.h"],  # Ensure this exists
    visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
)

# cc_library(
#     name = "bit-manipulation-tricks",
#     includes = ["include"],  # Include path for headers
#     srcs = ["bit-manipulation-tricks.cc"],
#     hdrs = ["//include/bitwise-operations:bit-manipulation-tricks.h"], 
#     visibility = ["//tests/bitwise-operations:__subpackages__"],  # Allow tests to use it
#     copts = ["-std=c++20", "-Iinclude/bitwise-operations"],
# )