cc_library(
    name = "codecs",
    includes = ["include"],  # Include path for headers
    srcs = ["vlq.cc"],
    hdrs = ["//include/codecs:vlq.h"],  # Ensure this exists
    visibility = ["//tests/codecs:__subpackages__"],  # Allow tests to use it
    copts = ["-std=c++20", "-Iinclude/codecs"],
)
