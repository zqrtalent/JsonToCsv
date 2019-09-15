#include "JsonCppFlattener.h"
#include <fstream>
#include <sys/stat.h>

JsonCppFlattener::JsonCppFlattener(){}

JsonCppFlattener::~JsonCppFlattener(){}

bool JsonCppFlattener::Flatten(const std::string& jsonFilePath, const std::string& flattenJsonPath){
    bool result = false;
    char* buffer = nullptr;
    unsigned int len = 0;

    ifstream istream(jsonFilePath);
    if(!istream){
        return result;
    }

    // get length of file:
    istream.seekg (0, istream.end);
    len = istream.tellg();
    istream.seekg (0, istream.beg);
    // Allocate buffer
    buffer = new char [len];
    // read data as a block:
    istream.read (buffer, len);
   
    Value rootObj;
    String errs;
    CharReaderBuilder rbuilder;
    std::unique_ptr<Json::CharReader> const reader(rbuilder.newCharReader());
    if(reader->parse(buffer, &buffer[len], &rootObj, &errs)){
        int buff_size = 1024, buff_used = 0;
        char* buffer_out = new char[buff_size];

        auto action = [&buffer_out, &buff_size, &buff_used](const Value& jVal, const string& propertyWithValue) {
            auto size = propertyWithValue.size();
            if((buff_size - buff_used) < size){
                buff_size = (buff_size <= 0 ? 1024 : 2*buff_size);
                char* newBuffer = new char[buff_size];
                if(buffer_out)
                    delete[] buffer_out;
                buffer_out = newBuffer;
            }

            memcpy(&buffer_out[buff_used], propertyWithValue.c_str(), size);
            buff_used += size;

            //cout << propertyWithValue << endl;
        };

        memcpy(buffer_out, "{", sizeof("{"));
        buff_used += sizeof("{");
        
        JsonCppFlattener::TraverseThroughChildren(rootObj, "$", action);
        // Overwrite last character.
        memcpy(&buffer_out[buff_used - 1], "}", sizeof("}"));

        // Write output flattened json file.
        ofstream jsonFileOut;
        jsonFileOut.open (flattenJsonPath);
        if(buff_used > 0)
            jsonFileOut.write(buffer_out, buff_used);
        jsonFileOut.close();

        if(buffer_out)
            delete[] buffer_out;
        result = true;
    }
    else{
        cout << "Error parsing json: " << errs << endl;
    }
    return result;
}


void JsonCppFlattener::TraverseThroughChildren(Value& obj, const string objJsonPath, std::function<void(const Value&, const string&)> action){
    char szBuffer[512];
    if(obj.isArray()){
        int loop = 0;
        for(Json::ValueIterator item = obj.begin(); item != obj.end() ; item++ ) {
            sprintf(szBuffer, "%s.%d.%s", objJsonPath.c_str(), loop++, item.name().c_str());
            JsonCppFlattener::TraverseThroughChildren(*item, szBuffer, action);
        }
    }
    else if(obj.isObject()){
        for(Json::ValueIterator item = obj.begin(); item != obj.end() ; item++ ) {
            JsonCppFlattener::TraverseThroughChildren(*item, objJsonPath + "." + item.name().c_str(), action);
        }
    }
    else{
        if(obj.isNumeric()){
            sprintf(szBuffer, "\"%s\":%s,", objJsonPath.c_str(), obj.asCString());
        }
        else{
            sprintf(szBuffer, "\"%s\":\"%s\",", objJsonPath.c_str(), obj.asCString());
        }
        action(obj, szBuffer);
    }
}