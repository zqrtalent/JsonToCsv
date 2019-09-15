#include "RapidJsonFlattener.h"
#include <fstream>
#include "reader.h"
#include "JsonPath.h"
#include "RapidJsonHandler.h"

using namespace rapidjson;

RapidJsonFlattener::RapidJsonFlattener(){
}

RapidJsonFlattener::~RapidJsonFlattener(){
}

bool RapidJsonFlattener::Flatten(const std::string& jsonFilePath, const std::string& flattenJsonPath){
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

    RapidJsonHandler handler;
    handler.bufferOut.Add("{", strlen("{"));

    Reader reader;
    StringStream ss(buffer);
    reader.Parse(ss, handler);

    ofstream jsonFileOut;
    jsonFileOut.open (flattenJsonPath);

    // Write output flattened json file.
    if(handler.bufferOut.GetBufferUsedSize() > 0){
        handler.bufferOut.PeekBuffer(-1*((int)strlen(",")));
        handler.bufferOut.Add("}", strlen("}"));
        
        jsonFileOut.write(handler.bufferOut.GetBuffer(), 
            handler.bufferOut.GetBufferUsedSize());
    }
    
    jsonFileOut.close();
    result = true;
    return result;
}