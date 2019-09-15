#ifndef JSONCPP_FLATTENER_H_INCLUDED
#define JSONCPP_FLATTENER_H_INCLUDED

#include <iostream>
#include "../JsonFlattener.h"
#include "jsoncpp/include/json.h"

using namespace std;
using namespace Json;

class JsonCppFlattener : public JsonFlattener{
public:
    JsonCppFlattener();
    virtual ~JsonCppFlattener();

    virtual bool Flatten(const std::string& jsonFilePath, const std::string& flattenJsonPath);
private:

    static void TraverseThroughChildren(Value& obj, const string objJsonPath, 
                std::function<void(const Value&, const string&)> action);

};

#endif //JSONCPP_FLATTENER_H_INCLUDED