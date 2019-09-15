#ifndef RAPIDJSON_FLATTENER_H_INCLUDED
#define RAPIDJSON_FLATTENER_H_INCLUDED

#include <iostream>
#include "../JsonFlattener.h"
using namespace std;

class RapidJsonFlattener : public JsonFlattener{
public:
    RapidJsonFlattener();
    virtual ~RapidJsonFlattener();

    virtual bool Flatten(const std::string& jsonFilePath, const std::string& flattenJsonPath);
};

#endif //RAPIDJSON_FLATTENER_H_INCLUDED