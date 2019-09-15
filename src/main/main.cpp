#include <iostream>
#include <fstream>
#include <sys/stat.h>
using namespace std;

#include "JsonCpp/JsonCppFlattener.h"
#include "RapidJson/RapidJsonFlattener.h"
#include "Stopwatch.h"

inline bool exists_test3 (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int main()
{
    Stopwatch sw;
    sw.Start();

    // auto add = [](int x, int y) {
    //   return x + y;
    // };
    // std::apply(add, std::make_tuple(1, 2)); // == 3

    // const auto bigFilePath {"bigFileToCopy"};
    // if (std::filesystem::exists(bigFilePath)) {   
    //   const auto bigFileSize {std::filesystem::file_size(bigFilePath)};
    //   std::filesystem::path tmpPath {"/tmp"};
    //   if (std::filesystem::space(tmpPath).available > bigFileSize) {
    //     std::filesystem::create_directory(tmpPath.append("example"));
    //     std::filesystem::copy_file(bigFilePath, tmpPath.append("newFile"));
    //   }
    // }

    // Start
    string json_file = "/json/sample1.json";
    string json_file_out = "/json/sample1_out.json";

    //JsonFlattener* flattener = new JsonCppFlattener(); 
    JsonFlattener* flattener = new RapidJsonFlattener();
    bool success = flattener->Flatten(json_file, json_file_out);

    sw.Stop();
    cout << "Finished in: " << sw.TotalSeconds() << "s!" << endl;
    // End
    return 0;
}