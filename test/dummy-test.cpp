#include "gtest/gtest.h"
#include "RapidJson/JsonPath.h"

TEST(JsonPathTest, GetPath) {
    JsonPath jPath;
    jPath.Push("array1", JsonPath::ComponentType::JArray);
    jPath.Push("1", JsonPath::ComponentType::JarrayElement, 1);
    jPath.Push("obj1", JsonPath::ComponentType::JObject);
    jPath.Push("val1", JsonPath::ComponentType::JProperty);
    EXPECT_EQ(jPath.GetPath(), "array1.1.obj1.val1");
}