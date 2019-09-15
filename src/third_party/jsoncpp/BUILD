cc_library(
    name = "jsoncpp",
    srcs = [
        "src/json_reader.cpp", 
        "src/json_value.cpp", 
        "src/json_writer.cpp"],
    hdrs = [
        "src/json_tool.h", 
        "src/json_valueiterator.inl", 
        "include/allocator.h",
        "include/assertions.h",
        "include/autolink.h",
        "include/config.h",
        "include/features.h",
        "include/forwards.h",
        "include/json.h",
        "include/reader.h",
        "include/value.h",
        "include/version.h",
        "include/writer.h"
    ],
    #visibility = ["//src:__pkg__"],
    visibility = ["//visibility:public"],
)

genrule(
    name = "jsoncpp_dsym",
    srcs = ["//src/third_party/jsoncpp:jsoncpp"],
    outs = ["libjsoncpp.dSYM"],
    output_to_bindir = True,
    cmd = "dsymutil $(locations //src/third_party/jsoncpp:jsoncpp)[0] -o $@"
)