cc_library(
    name = "services",
    srcs = [
        "JsonCpp/JsonCppFlattener.cpp",
        "JsonCpp/JsonCppFlattener.h",
        "RapidJson/RapidJsonFlattener.cpp",
        "RapidJson/RapidJsonFlattener.h",
        "RapidJson/JsonPath.h",
        "RapidJson/RapidJsonHandler.h",
        "JsonFlattener.h",
        "ResizableBuffer.h",
        "Stopwatch.h",
    ],
    deps = [
        "//src/third_party/jsoncpp:jsoncpp",
        "//src/third_party/rapidjson:rapidjson"
    ],
    includes = [
        "../third_party",
    ],
    strip_include_prefix = "services",
    visibility = [
        "//src/main:__pkg__",
        "//test:__pkg__"
    ]
    #visibility = ["//visibility:public"],
)