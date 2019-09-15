cc_test(
    name = "main-test",
    srcs = ["dummy-test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:gtest_lib",
        "//src/services:services",
    ],
    includes = [
        "../src/services"
    ]
)