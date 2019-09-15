#ifndef JSON_FLATTENER_H_INCLUDED
#define JSON_FLATTENER_H_INCLUDED

#include <iostream>
using namespace std;

class JsonFlattener{
public:
    virtual bool Flatten(const std::string& jsonFilePath, const std::string& flattenJsonPath) = 0;
};
#endif //JSON_FLATTENER_H_INCLUDED