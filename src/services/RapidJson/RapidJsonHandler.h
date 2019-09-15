#ifndef RAPID_JSON_HANDLER_H_INCLUDED
#define RAPID_JSON_HANDLER_H_INCLUDED

#include <iostream>
#include "reader.h"
#include "JsonPath.h"
#include "../ResizableBuffer.h"

using namespace rapidjson;
using namespace std;

struct RapidJsonHandler {
    JsonPath currPath;
    int arrayIndex;
    string currentKey;
    JsonPath::ComponentType currComponentType;
    JsonPath::PathComponent currComponent;
    char szKeyWithValue[512];
    ResizableBuffer bufferOut;

    bool Null() { 
        //cout << "Null()" << endl; 
        AsStringValue("null");
        return true; 
    }
    
    bool Bool(bool b) { 
        //cout << "Bool(" << boolalpha << b << ")" << endl; 
        AsStringValue(std::to_string(b));
        return true; 
        }
    
    bool Int(int i) { 
        //cout << "Int(" << i << ")" << endl; 
        AsStringValue(std::to_string(i));
        return true; 
    }
    
    bool Uint(unsigned u) { 
        //cout << "Uint(" << u << ")" << endl;
        AsStringValue(std::to_string(u));
        return true; 
    }
    
    bool Int64(int64_t i) { 
        //cout << "Int64(" << i << ")" << endl; 
        AsStringValue(std::to_string(i));
        return true; 
    }
    
    bool Uint64(uint64_t u) { 
        //cout << "Uint64(" << u << ")" << endl;
        AsStringValue(std::to_string(u));
        return true; 
    }
    
    bool Double(double d) { 
        //cout << "Double(" << d << ")" << endl;
        AsStringValue(std::to_string(d));
        return true; 
    }

    bool RawNumber(const char* str, SizeType length, bool copy) { 
        //cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        AsStringValue(str, true);
        return true;
    }

    bool String(const char* str, SizeType length, bool copy) { 
        //cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        AsStringValue(str, true);
        return true;
    }

    void AsStringValue(const std::string value, bool isString = false){
        std::string path;
        // Add array item.
        if(currComponentType == JsonPath::ComponentType::JArray)
            path = currPath.CombinePath(std::to_string(arrayIndex++));
        else
            path = currPath.CombinePath(currentKey);

        int len = 0;
        if(isString)
            len = std::sprintf(szKeyWithValue, "\"%s\":\"%s\",", path.c_str(), value.c_str());
        else
            len = std::sprintf(szKeyWithValue, "\"%s\":%s,", path.c_str(), value.c_str());
        bufferOut.Add(szKeyWithValue, len);
        //cout << path << ":" << value << endl;
    }

    bool StartObject() { 
        //cout << "StartObject()" << endl;
        //Array item.
        if(currComponentType == JsonPath::ComponentType::JArray){
            currPath.Push(std::to_string(arrayIndex), JsonPath::ComponentType::JarrayElement, arrayIndex++);
        }
        else{
            currPath.Push(currentKey, JsonPath::ComponentType::JObject);
        }
        currComponentType = JsonPath::ComponentType::JObject;
        return true; 
    }

    bool EndObject(SizeType memberCount) { 
        //cout << "EndObject(" << memberCount << ")" << endl;
        if(!currPath.Pop(currComponent)){
            currPath.SetTailIndex(arrayIndex);
            currComponentType = JsonPath::ComponentType::JObject;
            arrayIndex = 0;
        }
        else{
            currComponentType = currComponent.type;
            arrayIndex = currComponent.index;
        }
        return true; 
    }

    bool StartArray() { 
        //cout << "StartArray()" << endl; 
        if(currComponentType == JsonPath::ComponentType::JArray){
            currPath.SetTailIndex(arrayIndex + 1);
            currentKey = std::to_string(arrayIndex);
        }
        
        arrayIndex = 0;
        currComponentType = JsonPath::ComponentType::JArray;
        currPath.Push(currentKey, currComponentType, arrayIndex);
        return true;
    }

    bool EndArray(SizeType elementCount) { 
        //cout << "EndArray(" << elementCount << ")" << endl; 
        if(!currPath.Pop(currComponent)){
            currComponentType = JsonPath::ComponentType::JObject;
            arrayIndex = 0;
        }
        else{
            currComponentType = currComponent.type;
            arrayIndex = currComponent.index;
        }
        return true; 
    }

    bool Key(const char* str, SizeType length, bool copy) {
        //cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        currentKey = string(str, length); // Keep current key
        return true;
    }
};

#endif //RAPID_JSON_HANDLER_H_INCLUDED