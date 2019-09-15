cc_binary(
    name = "main",
    srcs = [
        "main/main.cpp", 
    ],
    deps = [
        "//src/services:services",
    ],
    includes = [
        "services"
    ]
)

genrule(
    name = "main_dsym",
    srcs = [":main"],
    outs = ["main.dSYM"],
    output_to_bindir = True,
    cmd = "dsymutil $(location :main) -o $@"
)